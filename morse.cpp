#include "morse.h"

Morse::Morse(uint8_t outputPin, uint8_t listenPin, uint32_t rate, uint8_t tonePin) {
        _output_pin = outputPin;
        _listen_pin = listenPin;
        _rate = rate;
        _speaker_pin = tonePin;
        txTimer = new Timer(_rate, &Morse::transmitting, *this);
};

void Morse::begin(void) {
    pinMode(_output_pin, OUTPUT);
    pinMode(_listen_pin, INPUT_PULLDOWN);
};

// argument a string, returns binary morse code
void Morse::encode( String message ) {

    morseEncoded.clear();
    wordSingle = false;

    for (int letter = 0; letter < message.length(); letter++) {
        if(message[letter] == ' ') {
            // void insert (iterator position, InputIterator first, InputIterator last);
            // binaryMorse.insert(binaryMorse.end(), more.begin(), more.end());

            // add wordSpace
            for(uint8_t space = 0; space < 7; space++) {
                morseEncoded.push_back('0');
            };

            wordSingle = false;

        } else {

            // add letterSpace if the last char was a letter
            if(wordSingle == true) {
                for(uint8_t space = 0; space < 3; space++) {
                    morseEncoded.push_back('0');
                };
            };


            // match character
            for(uint8_t character = 0; character < sizeof(letterFrequency); character++) {      // sizeof(letterFrequency)    letterFrequency.size()
                if( message[letter] == letterFrequency[character] ) {
                    // add binaryMorse[character]
                    for(uint8_t part = 0; part < 19; part++) {
                        if(binaryMorse[character][part] != 0) {
                            morseEncoded.push_back(binaryMorse[character][part]);
                        };
                    };
                };
                wordSingle = true;
            };
        };
    };
    // additional end of message?
    morseEncoded.push_back('0');
};

void Morse::send(void) {
    // mask the individual bit, or have a pointer to the bit, maybe a pointer to the char and mask the bit
    txPosition = 0;

    txTimer->start();
};

// continues to call until full message is sent
void Morse::transmitting(void) {

    switch( morseEncoded[txPosition] ) {
        case '0':
            outLow();
        break;
        case '1':
            outHigh();
        break;
        default:
        break;
    };

    // Particle.publish( String(txPosition), String( morseEncoded[txPosition]) );
    txPosition++;
    if( txPosition > morseEncoded.size() - 1 ) {
        stop();
    };
    // Particle.publish( "size of encoded", String( morseEncoded.size() ) );
};

void Morse::outHigh(void) {
    if( pinReadFast(_output_pin) == LOW ) {
        digitalWriteFast(_output_pin, HIGH);
        tone(_speaker_pin, _rate);
    };
};

void Morse::outLow(void) {
    digitalWriteFast(_output_pin, LOW);
    noTone(_speaker_pin);
};

void Morse::stop(void) {
    txTimer->stop();
};

void Morse::listen(void) {
    attachInterrupt(_listen_pin, &Morse::receiving, CHANGE);
    Particle.publish( "listening" );
};

void Morse::receiving(void) {

    // store a pair of values [HIGH/LOW, millis]
    morseRx.push_back(std::make_tuple( millis(), pinReadFast(_listen_pin) ) );
    Particle.publish( "receiving" );

};

void Morse::decode(void) {

    var time tick1 = std::get<0>(morseRx[0]);
    var time tick2 = std::get<1>(morseRx[0]);
    var time tick3 = std::get<2>(morseRx[0]);
    var time tick4 = std::get<3>(morseRx[0]);
    // mills 1-0 = time, value of 0 = high or low
    // time = 1 unit, value low interletter high dit
    // time = 3 units, value low next letter high dah
    // time = 7 units, value low space
    // time > 8 new message

    // morseTiming

    // Edit/Update: if you were looping over you vector and i is your integer index used during the loop, then to access to tuple you can do this:
    //
    // int intOne, intTwo;
    //
    // intOne = std::get<0>(ints[i]);
    // intTwo = std::get<1>(ints[i]);

    Particle.publish( "Mills1", String( tick1 ) );
    Particle.publish( "Mills2", String( tick2 ) );
    Particle.publish( "Mills3", String( tick3 ) );
    Particle.publish( "Mills4", String( tick4 ) );

};
