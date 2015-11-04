#include <cmath>
#include <iostream>

#include <DE.h>
#include <ANN.h>
#include <Counter.h>
#include <TimePeriod.h>
#include <TrainingSet.h>
#include <ModelParameters.h>

using namespace std;

bool isRunning = true;

void sleep() {
}

int main(){
    srand( time(NULL) );

    char symbol[ 10 ];
    TimePeriod period;
    Counter counters;
    ANN ann(&counters, 12, 5, 1, M1);
    DE de(&counters, &ann, 13);
    TrainingSet ts;

    ann.setupInput( 5 );
	ann.setupOutput( 1 );
	ann.setupThreeLayers();

    /*
     * Implement simple rates test case.
     */
    std::vector<RateInfo> &rates = ts.getRates();
    rates.resize(31);
    for(int i=0; i<rates.size(); i++) {
        //TODO May be it should be in the oposite direction.
        rates[i].time = rates.size()-i-1;

        rates[i].open = (1 + sin((double)i/rates.size()*M_PI+M_PI/17.0)) / 2.0;
        rates[i].low = (1 + sin((double)i/rates.size()*M_PI+M_PI/19.0)) / 2.0;
        rates[i].high = (1 + sin((double)i/rates.size()*M_PI+M_PI/23.0)) / 2.0;
        rates[i].close = (1 + sin((double)i/rates.size()*M_PI+M_PI/31.0)) / 2.0;

        rates[i].volume = rand();
    }

	ann.setTrainingSetPointer( &ts );

    cout << "===" << endl;
    cout << endl;
    //cout << ann << endl;
    cout << endl;
    cout << "===" << endl;
    cout << endl;
    //cout << de << endl;
    cout << endl;
    cout << "===" << endl;
    cout << endl;
    //cout << ts << endl;
    cout << endl;
    cout << "===" << endl;
    cout << endl;

    return EXIT_SUCCESS;
}
