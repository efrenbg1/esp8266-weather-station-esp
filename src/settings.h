/**The MIT License (MIT)
 
 Copyright (c) 2018 by ThingPulse Ltd., https://thingpulse.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <Arduino.h>
#include <TZ.h>

const int UPDATE_INTERVAL_SECS = 10 * 60; // Update every 10 minutes
const unsigned long TOUCH_DEBOUCE_TIME = 200;
const unsigned long SCREEN_TIMEOUT = 30000;
const unsigned long TFT_LED_TIMEOUT_NIGHT = 5000;

/*
Go to https://openweathermap.org/find?q= and search for a location. Go through the
result set and select the entry closest to the actual location you want to display 
data for. It'll be a URL like https://openweathermap.org/city/2657896. The number
at the end is what you assign to the constant below.
 */
String OPEN_WEATHER_MAP_LOCATION_ID = "6359348";
String DISPLAYED_CITY_NAME = "Las Rozas de Madrid";
/*
Arabic -> ar, Bulgarian -> bg, Catalan -> ca, Czech -> cz, German -> de, Greek -> el,
English -> en, Persian (Farsi) -> fa, Finnish -> fi, French -> fr, Galician -> gl,
Croatian -> hr, Hungarian -> hu, Italian -> it, Japanese -> ja, Korean -> kr,
Latvian -> la, Lithuanian -> lt, Macedonian -> mk, Dutch -> nl, Polish -> pl,
Portuguese -> pt, Romanian -> ro, Russian -> ru, Swedish -> se, Slovak -> sk,
Slovenian -> sl, Spanish -> es, Turkish -> tr, Ukrainian -> ua, Vietnamese -> vi,
Chinese Simplified -> zh_cn, Chinese Traditional -> zh_tw.
*/
String OPEN_WEATHER_MAP_LANGUAGE = "es";

// Adjust according to your language
const String WDAY_NAMES[] = {"DO", "LU", "MA", "MI", "JU", "VI", "SA"};
const String MONTH_NAMES[] = {"ENE", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AGO", "SEP", "OCT", "NOV", "DIC"};
const String SUN_MOON_TEXT[] = {"Sol", "Sal.", "Pue.", "Luna", "Edad", "Illum"};
const String MOON_PHASES[] = {"Luna Nueva", "Luna Creciente", "Cuarto Creciente", "Gibosa Creciente",
                              "Luna Llena", "Gibosa Menguante", "Cuarto Menguante", "Luna Menguante"};

// pick one from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
#define TIMEZONE TZ_Europe_Madrid

// values in metric or imperial system?
const boolean IS_METRIC = true;

// Change for 12 Hour/ 24 hour style clock
bool IS_STYLE_12HR = false;

// change for different NTP (time servers)
#define NTP_SERVERS "1.es.pool.ntp.org", "2.europe.pool.ntp.org", "0.europe.pool.ntp.org"
// #define NTP_SERVERS "us.pool.ntp.org", "time.nist.gov", "pool.ntp.org"

// August 1st, 2018
#define NTP_MIN_VALID_EPOCH 1533081600

// Pins for the ILI9341
#define TFT_DC D2
#define TFT_CS D1
#define TFT_LED D8

#define HAVE_TOUCHPAD
#define TOUCH_CS D3
#define TOUCH_IRQ D4

/***************************
 * End Settings
 **************************/
