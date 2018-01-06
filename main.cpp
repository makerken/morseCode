// This #include statement was automatically added by the Particle IDE.
#include "morse.h"

Morse morse(D7, D2, 200, D1);   // output, input, rate, tone

void setup() {

    Particle.function("message", morseFxn);
	morse.begin();

}

void loop() {

}

int morseFxn( String message ) {

    morse.encode( message );

    morse.send();

    return 1;

}
