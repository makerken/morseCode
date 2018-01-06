#include "morse.h"

Morse::Morse(uint8_t outputPin, uint8_t listenPin, uint32_t rate, uint8_t tonePin) {
        _output_pin = outputPin;
        _listen_pin = listenPin;
        _rate = rate;
        _speaker_pin = tonePin;
        txTimer = new Timer(_rate, &Morse::transmitting, *this);
        rxTimer = new Timer(_rate, &Morse::receiving, *this);
};

void Morse::begin(void) {
    pinMode(_output_pin, OUTPUT);
    pinMode(_listen_pin, INPUT);
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

// stop the timers
void Morse::stop(void) {
    txTimer->stop();
    rxTimer->stop();
};

void Morse::receiving(void) {
    rxTimer->start();
    // set an interrupt to listen for changes on the listening pin
    // continues to call until end of message of blank for 3sec
    digitalWrite(_output_pin, !digitalRead(_output_pin) );
};

void Morse::outHigh(void) {
    if( pinReadFast(_output_pin) == LOW ) {
        digitalWriteFast(_output_pin, HIGH);
        tone(_speaker_pin, 1000);
    };
};

void Morse::outLow(void) {
    digitalWriteFast(_output_pin, LOW);
    noTone(_speaker_pin);
};
