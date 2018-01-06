#include "Particle.h"
#include <vector>

class Morse{
    public:
        Morse(uint8_t, uint8_t, uint32_t, uint8_t);
        void begin(void);
        void encode( String );
        void send(void);
        void transmitting(void);
        void receiving(void);
        void stop(void);
        volatile int txPosition;
        // decode
        std::vector<unsigned char> morseEncoded = {};

    private:
        void outHigh(void);
        void outLow(void);
        uint8_t _output_pin;
        uint8_t _listen_pin;
        uint32_t _rate;
        uint8_t _speaker_pin;
        Timer *txTimer;
        Timer *rxTimer;
        bool wordSingle = false;
        // the ordered frequency of letters in english
        char letterFrequency[47] = {'e','t','a','o','i','n','s','r','h','l','d','c','u','m','f',
        'p','g','w','y','b','v','k','x','j','q','z','1','2','3','4','5','6','7','8','9','0','.',
        ',',':','?','‘','-','/','(','“','@'};

        // binary array of morse codes for each letter
        uint8_t binaryMorse[47][19] = {
        	{'1'},																			// e
        	{'1','1','1'},																	// t
        	{'1','0','1','1','1'},															// a
        	{'1','1','1','0','1','1','1','0','1','1','1'},									// o
        	{'1','0','1'},											                    	// i
        	{'1','1','1','0','1'},												            // n
        	{'1','0','1','0','1'},												            // s
        	{'1','0','1','1','1','0','1'},											    	// r
        	{'1','0','1','0','1','0','1'},												    // h
        	{'1','0','1','1','1','0','1','0','1'},											// l
        	{'1','1','1','0','1','0','1'},												    // d
        	{'1','1','1','0','1','0','1','1','1','0','1'},									// c
        	{'1','0','1','0','1','1','1'},												    // u
        	{'1','1','1','0','1','1','1'},												    // m
        	{'1','0','1','0','1','1','1','0','1'},											// f
        	{'1','0','1','1','1','0','1','1','1','0','1'},									// p
        	{'1','1','1','0','1','1','1','0','1'},											// g
        	{'1','0','1','1','1','0','1','1','1'},											// w
        	{'1','1','1','0','1','0','1','1','1','0','1','1','1'},							// y
        	{'1','1','1','0','1','0','1','0','1'},										    // b
        	{'1','0','1','0','1','0','1','1','1'},											// v
        	{'1','1','1','0','1','0','1','1','1'},											// k
        	{'1','1','1','0','1','0','1','0','1','1','1'},									// x
        	{'1','0','1','1','1','0','1','1','1','0','1','1','1'},							// j
        	{'1','1','1','0','1','1','1','0','1','0','1','1','1'},							// q
        	{'1','1','1','0','1','1','1','0','1','0','1'},									// z
        	{'1','0','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1'},			// 1
        	{'1','0','1','0','1','1','1','0','1','1','1','0','1','1','1'},					// 2
        	{'1','0','1','0','1','0','1','1','1','0','1','1','1'},							// 3
        	{'1','0','1','0','1','0','1','0','1','1','1'},									// 4
        	{'1','0','1','0','1','0','1','0','1'},								        	// 5
        	{'1','1','1','0','1','0','1','0','1','0','1'},									// 6
        	{'1','1','1','0','1','1','1','0','1','0','1','0','1'},							// 7
        	{'1','1','1','0','1','1','1','0','1','1','1','0','1','0','1'},					// 8
        	{'1','1','1','0','1','1','1','0','1','1','1','0','1','1','1','0','1'},			// 9
        	{'1','1','1','0','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1'},	// 0
        	{'1','0','1','1','1','0','1','0','1','1','1','0','1','0','1','1','1'},			// .
        	{'1','1','1','0','1','1','1','0','1','0','1','0','1','1','1','0','1','1','1'},	// ,
        	{'1','1','1','0','1','1','1','0','1','1','1','0','1','0','1','0','1'},			// :
        	{'1','0','1','0','1','1','1','0','1','1','1','0','1','0','1'},					// ?
        	{'1','0','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1','0','1'},	// ‘
        	{'1','1','1','0','1','0','1','0','1','0','1','0','1','1','1'},			    	// -
        	{'1','1','1','0','1','0','1','0','1','1','1','0','1'},							// /
        	{'1','1','1','0','1','0','1','1','1','0','1','1','1','0','1','0','1','1','1'},	// (
        	{'1','0','1','1','1','0','1','0','1','0','1','1','1','0','1'},					// “
        	{'1','0','1','1','1','0','1','1','1','0','1','0','1','1','1','0','1'},			// @
        	{'1','1','1','0','1','0','1','0','1','0','1','1','1'}							// =
        };

};