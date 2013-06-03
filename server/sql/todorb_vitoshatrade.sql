-- phpMyAdmin SQL Dump
-- version 3.5.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Sep 13, 2012 at 11:37 AM
-- Server version: 5.5.25a
-- PHP Version: 5.4.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `veldsoft_vitoshatrade`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `insertCurrencyPair`(IN `symbol` VARCHAR(255), IN `period` INT(10))
    MODIFIES SQL DATA
    COMMENT 'Insert currency pair with currency symbol and minutes period.'
begin
	declare period_id int;
        
        select id into period_id from time_periods where time_periods.minutes=period;
        
	insert into currency_pairs (symbol, period_id, description) values (symbol, period_id, "");
end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `saveAnn`(IN `symbol` VARCHAR(255), IN `period` INT(10), IN `number_of_neurons` INT(10), IN `flags` TEXT, IN `activities` TEXT, IN `fitness` DOUBLE, IN `weights` TEXT)
    MODIFIES SQL DATA
    COMMENT 'Save ANN information in many tables.'
begin
	declare currency_pairs_id int;
        declare ann_kind_id int;
        
        set currency_pairs_id = checkCurrencyPairsId(symbol,period);
	if currency_pairs_id=0 then
        	call insertCurrencyPair(symbol, period);
        	set currency_pairs_id = checkCurrencyPairsId(symbol,period);
        end if;

	set ann_kind_id = checkAnnKindId(symbol, period, number_of_neurons, flags, activities);
        if ann_kind_id=0 then
		insert into ann_kind (currency_pairs_id, number_of_neurons, flags, activities) values (currency_pairs_id, number_of_neurons, flags, activities);
                set ann_kind_id = checkAnnKindId(symbol, period, number_of_neurons, flags, activities);
	end if;

	insert into ann (ann_kind_id, fitness, weights) values (ann_kind_id, fitness, weights);
        
end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `saveTrainingSet`(IN `symbol` VARCHAR(255), IN `period` INT, IN `number_of_examples` INT, IN `time` TEXT, IN `open` TEXT, IN `low` TEXT, IN `high` TEXT, IN `close` TEXT, IN `volume` TEXT)
    MODIFIES SQL DATA
    COMMENT 'Save training set values.'
begin
	declare currency_pairs_id int;
	declare id int;
        
        set currency_pairs_id = checkCurrencyPairsId(symbol,period);
	if currency_pairs_id=0 then
        	call insertCurrencyPair(symbol, period);
        	set currency_pairs_id = checkCurrencyPairsId(symbol,period);
        end if;

	-- Delete previous record, because information will be old.
        select training_set.id into id from training_set, currency_pairs, time_periods where training_set.currency_pairs_id=currency_pairs.id and currency_pairs.period_id=time_periods.id and currency_pairs.symbol=symbol and time_periods.minutes=period;
	delete from training_set where training_set.id = id;
        
        -- Insert new data for the same record.
        insert into training_set (training_set.currency_pairs_id, training_set.number_of_examples, training_set.time, training_set.open, training_set.low, training_set.high, training_set.close, training_set.volume) values (currency_pairs_id, number_of_examples, time, open, low, high, close, volume);
end$$

--
-- Functions
--
CREATE DEFINER=`root`@`localhost` FUNCTION `checkAnnKindId`(`symbol` VARCHAR(255), `period` INT(10), `number_of_neurons` INT(10), `flags` TEXT, `activities` TEXT) RETURNS int(11)
    READS SQL DATA
    COMMENT 'Check for ANN kind id. Return 0 if it was not found.'
begin
	declare id int;

        select ann_kind.id into id from ann_kind, currency_pairs, time_periods where ann_kind.currency_pairs_id=currency_pairs.id and currency_pairs.period_id=time_periods.id and currency_pairs.symbol=symbol and time_periods.minutes=period and ann_kind.number_of_neurons=number_of_neurons and ann_kind.flags=flags and activities=activities;
        
        if id is null then
        	set id = 0;
        end if;
        
	return id;
end$$

CREATE DEFINER=`root`@`localhost` FUNCTION `checkCurrencyPairsId`(`symbol` VARCHAR(255), `period` INT(10)) RETURNS int(11)
    READS SQL DATA
    COMMENT 'Check for currency pair id. Return 0 if it was not found.'
begin

	declare id int;

        select currency_pairs.id into id from currency_pairs, time_periods where currency_pairs.period_id=time_periods.id and currency_pairs.symbol=symbol and time_periods.minutes=period;
        
        if id is null then
        	set id = 0;
        end if;
        
	return id;

end$$

CREATE DEFINER=`root`@`localhost` FUNCTION `listAnns`(`id` INT) RETURNS text CHARSET utf8 COLLATE utf8_unicode_ci
    READS SQL DATA
    COMMENT 'List ids of all ANN from particular type.'
begin
	declare ids text;
        
        -- TODO Implement list of ANNs.
        
        return ids;
end$$

CREATE DEFINER=`root`@`localhost` FUNCTION `loadBestFitness`(`symbol` VARCHAR(255), `period` INT, `number_of_neurons` INT, `flags` TEXT, `activities` TEXT) RETURNS double
    READS SQL DATA
    COMMENT 'Load best fitness for particular ANN kind.'
begin
	declare best double;
        declare ann_kind_id int;
        
	select ann_kind.id into ann_kind_id from ann_kind, currency_pairs, time_periods where currency_pairs.symbol=symbol and time_periods.minutes=period and ann_kind.number_of_neurons=number_of_neurons and ann_kind.flags=flags and ann_kind.activities=activities and ann_kind.currency_pairs_id=currency_pairs.id and currency_pairs.period_id=time_periods.id;

        select min(ann.fitness) into best from ann where ann.ann_kind_id=ann_kind_id;
        
        if best is null then
        	set best = 10000;
        end if;
        
	return best;
end$$

CREATE DEFINER=`root`@`localhost` FUNCTION `loadNeuronsAmount`(`id` INT) RETURNS int(11)
    READS SQL DATA
    COMMENT 'Check neurons amount in particular ANN.'
begin
	declare amount int;

	select ann_kind.number_of_neurons into amount from ann, ann_kind where ann.id=id and ann.ann_kind_id=ann_kind.id;
        
        if amount is null then
        	set amount = 0;
        end if;
        
        return amount;
end$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `ann`
--

CREATE TABLE IF NOT EXISTS `ann` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Artificial neural network unique identifier.',
  `ann_kind_id` int(11) NOT NULL COMMENT 'Artificial neural network kind foreign key.',
  `fitness` double unsigned NOT NULL COMMENT 'Artificial neural network weights fitness.',
  `weights` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Artificial neural network weights.',
  PRIMARY KEY (`id`),
  KEY `ann_kind_id` (`ann_kind_id`,`fitness`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Artificial neural network.' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `ann_kind`
--

CREATE TABLE IF NOT EXISTS `ann_kind` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Artificial neural network unique identifier.',
  `currency_pairs_id` int(11) NOT NULL COMMENT 'MetaTrader 4 chart currency pair ID.',
  `number_of_neurons` int(10) unsigned NOT NULL COMMENT 'Number of neurons used for artificial neural network.',
  `flags` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Neurons flags (bias, input, output).',
  `activities` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Artificial neural network weights activities.',
  PRIMARY KEY (`id`),
  KEY `symbol` (`currency_pairs_id`,`number_of_neurons`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Artificial neural network kind.' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `currency_pairs`
--

CREATE TABLE IF NOT EXISTS `currency_pairs` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Currency pairs unique identifier.',
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL COMMENT 'MetaTrader 4 chart symbol.',
  `period_id` int(11) NOT NULL COMMENT 'Time period ID.',
  `description` varchar(255) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Describe what kind of currency pair.',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `neurons_coordinates`
--

CREATE TABLE IF NOT EXISTS `neurons_coordinates` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Unique identifier.',
  `ann_id` int(11) NOT NULL COMMENT 'Link to ANN table.',
  `coordinates` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Neurons coordinates (x, y).',
  PRIMARY KEY (`id`),
  UNIQUE KEY `ann_id` (`ann_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Backend neurons visualisation information.' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `time_periods`
--

CREATE TABLE IF NOT EXISTS `time_periods` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Unique identifier.',
  `minutes` int(11) NOT NULL COMMENT 'Number of minutes.',
  `period` varchar(10) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Time period as symbols.',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Time periods minutes to symbols mapping.' AUTO_INCREMENT=10 ;

--
-- Dumping data for table `time_periods`
--

INSERT INTO `time_periods` (`id`, `minutes`, `period`) VALUES
(1, 1, 'M1'),
(2, 5, 'M5'),
(3, 15, 'M15'),
(4, 30, 'M30'),
(5, 60, 'H1'),
(6, 240, 'H4'),
(7, 1440, 'D1'),
(8, 10080, 'W1'),
(9, 43200, 'MN1');

-- --------------------------------------------------------

--
-- Table structure for table `training_options`
--

CREATE TABLE IF NOT EXISTS `training_options` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Training options unique identifier.',
  `ann_id` int(11) NOT NULL COMMENT 'Link to ANN table.',
  `de_population_size` int(10) unsigned NOT NULL COMMENT 'Differencial evolution population size.',
  `number_of_training_bars` int(10) unsigned NOT NULL COMMENT 'Number of traning bars to be used for training process.',
  `after_bars_prediction` int(10) NOT NULL COMMENT 'Prediction after number of bars (it can be negative).',
  PRIMARY KEY (`id`),
  UNIQUE KEY `ann_id` (`ann_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Artificial neural network training options.' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `training_set`
--

CREATE TABLE IF NOT EXISTS `training_set` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Unique identifier.',
  `currency_pairs_id` int(11) NOT NULL COMMENT 'Currency pair ID.',
  `number_of_examples` int(11) NOT NULL COMMENT 'Number of training examples.',
  `time` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Time values of the time series.',
  `open` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Open values of time series.',
  `low` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Low values of time series.',
  `high` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'High values of time series.',
  `close` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Close values of time series.',
  `volume` longtext COLLATE utf8_unicode_ci NOT NULL COMMENT 'Volume values of time series.',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Training set examples table.' AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
