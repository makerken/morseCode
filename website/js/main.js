function Morse( timeUnit, toneFrequency ) {

    timeUnit = (typeof timeUnit === 'undefined') ? 80 : timeUnit;
    var timeunit = timeUnit;

    toneFrequency = (typeof toneFrequency === 'undefined') ? 600 : toneFrequency;
    var frequency = toneFrequency;

    var tone = new Tone.Oscillator(frequency, "sine").toMaster();

    var txPosition = 0;
    var txTimer;
    var binaryMorse = [];
    var wordSingle = false;

    var morseCodes = {
        "e" : [1],
        "t" : [1,1,1],
        "a" : [1,0,1,1,1],
        "o" : [1,1,1,0,1,1,1,0,1,1,1],
        "i" : [1,0,1],
        "n" : [1,1,1,0,1],
        "s" : [1,0,1,0,1],
        "r" : [1,0,1,1,1,0,1],
        "h" : [1,0,1,0,1,0,1],
        "l" : [1,0,1,1,1,0,1,0,1],
        "d" : [1,1,1,0,1,0,1],
        "c" : [1,1,1,0,1,0,1,1,1,0,1],
        "u" : [1,0,1,0,1,1,1],
        "m" : [1,1,1,0,1,1,1],
        "f" : [1,0,1,0,1,1,1,0,1],
        "p" : [1,0,1,1,1,0,1,1,1,0,1],
        "g" : [1,1,1,0,1,1,1,0,1],
        "w" : [1,0,1,1,1,0,1,1,1],
        "y" : [1,1,1,0,1,0,1,1,1,0,1,1,1],
        "b" : [1,1,1,0,1,0,1,0,1],
        "v" : [1,0,1,0,1,0,1,1,1],
        "k" : [1,1,1,0,1,0,1,1,1],
        "x" : [1,1,1,0,1,0,1,0,1,1,1],
        "j" : [1,0,1,1,1,0,1,1,1,0,1,1,1],
        "q" : [1,1,1,0,1,1,1,0,1,0,1,1,1],
        "z" : [1,1,1,0,1,1,1,0,1,0,1],
        "1" : [1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1],
        "2" : [1,0,1,0,1,1,1,0,1,1,1,0,1,1,1],
        "3" : [1,0,1,0,1,0,1,1,1,0,1,1,1],
        "4" : [1,0,1,0,1,0,1,0,1,1,1],
        "5" : [1,0,1,0,1,0,1,0,1],
        "6" : [1,1,1,0,1,0,1,0,1,0,1],
        "7" : [1,1,1,0,1,1,1,0,1,0,1,0,1],
        "8" : [1,1,1,0,1,1,1,0,1,1,1,0,1,0,1],
        "9" : [1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1],
        "0" : [1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1],
        "." : [1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1],
        "," : [1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1],
        ":" : [1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1],
        "?" : [1,0,1,0,1,1,1,0,1,1,1,0,1,0,1],
        "‘" : [1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1],
        "-" : [1,1,1,0,1,0,1,0,1,0,1,0,1,1,1],
        "/" : [1,1,1,0,1,0,1,0,1,1,1,0,1],
        "(" : [1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1],
        "“" : [1,0,1,1,1,0,1,0,1,0,1,1,1,0,1],
        "@" : [1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1],
        "=" : [1,1,1,0,1,0,1,0,1,0,1,1,1],
    };

    this.encode = function( message ) {

        message = message.toLowerCase();
        binaryMorse = [];
        var wordSpace = [0,0,0,0,0,0,0];
        var letterSpace = [0,0,0];

        for (var character = 0; character < message.length; character++) {

            if( message[character] == " " ) {
                binaryMorse = binaryMorse.concat( wordSpace );
                wordSingle = false;
            } else {
                if(wordSingle == true) {
                    binaryMorse = binaryMorse.concat( letterSpace );
                }
                binaryMorse = binaryMorse.concat( morseCodes[ message[character] ] );
                wordSingle = true;
            }

        }

        // binaryMorse = binaryMorse.concat( wordSpace );
        // binaryMorse = binaryMorse.concat( morseCodes[ value["a"] ] );
        // binaryMorse = binaryMorse.concat( morseCodes[ value["r"] ] );
        binaryMorse.push(0);       // turn off beeps

    };

    this.send = function( message ) {
        if( typeof message !== 'undefined' ) {
            this.encode( message );
        }
        txPosition = 0;
        txTimer = setTimeout( function(){ transmitting() }, timeunit );
    }

    this.stop = function() {
        clearTimeout(txTimer);
    }

    function transmitting() {
        if( txPosition < binaryMorse.length ) {
            if( binaryMorse[txPosition] === 1 ) {
                if( tone.state === "stopped" ) {
                    tone.start();
                }
            } else {
                tone.stop();
            }
            txPosition++;
            txTimer = setTimeout( function(){ transmitting() }, timeunit );
        }
    }
}
