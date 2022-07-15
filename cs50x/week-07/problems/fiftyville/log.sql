-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape

-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

-- find the reports for July 28th, 2020 and were on Chamberlin Street
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2020 AND street = "Chamberlin Street";
-- transcript should contain "courthouse"
-- Theft occured around 1015

-- look at transcripts that contain "courthouse"
select name, transcript from interviews WHERE year = 2020 and month = 7 and day = 28 AND transcript LIKE "%courthouse%";
-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Theft occured 1015-1025, call less than a minute, ATM transaction in the morning at Fifer street

-- look for security footage of courthouse parking lot during the theft to find vehicle
SELECT activity, license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- exit|5P2BI95
-- exit|94KL13X
-- exit|6P58WS2
-- exit|4328GD8
-- exit|G412CB7
-- exit|L93JTIZ
-- exit|322W7JE
-- exit|0NTHK55

-- look for calls around 1 minute long on day of theft
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 AND duration <= 60;
-- (130) 555-0289|(996) 555-8899
-- (499) 555-9472|(892) 555-8872
-- (367) 555-5533|(375) 555-8161
-- (609) 555-5876|(389) 555-5198
-- (499) 555-9472|(717) 555-1342
-- (286) 555-6063|(676) 555-6554
-- (770) 555-1861|(725) 555-3243
-- (031) 555-6622|(910) 555-3251
-- (826) 555-1652|(066) 555-9701
-- (338) 555-6650|(704) 555-2131

-- look for withdrawals on the same day on Fifer street
SELECT account_number FROM atm_transactions WHERE transaction_type = "withdraw" AND atm_location = "Fifer Street" AND year = 2020 AND month = 7 AND day = 28;
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199

-- account info query
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE transaction_type = "withdraw" AND atm_location = "Fifer Street" AND year = 2020 AND month = 7 AND day = 28);
-- 686048
-- 514354
-- 458378
-- 395717
-- 396669
-- 467400
-- 449774
-- 438727

-- cross reference peoples' phone numbers and license plate
SELECT name, id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 AND duration <= 60) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) AND ;
-- Roger|398010
-- Russell|514354
-- Evelyn|560886
-- Ernest|686048

-- Russell and Ernest are suspects

-- passport numbers of suspects
SELECT passport_number, name FROM people WHERE name LIKE "Russell" OR name LIKE "Ernest";
-- 3592750733|Russell
-- 5773159633|Ernest

-- look at flights based on city airport id and time of robbery
SELECT id FROM airports WHERE city LIKE "fiftyville";
-- 8

SELECT id, destination_airport_id, hour, minute FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city LIKE "Fiftyville")
AND year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute;
-- 36|4
-- 43|1
-- 23|11
-- 53|9
-- 18|6

-- cross-reference passport numbers with passengers and outgoing flights above
SELECT name, phone_number FROM people JOIN passengers ON passengers.passport_number = people.passport_number JOIN flights ON flights.id = passengers.flight_id WHERE flights.id = 36;
-- Ernest|(367) 555-5533

-- cross-reference license plate numbers
SELECT name, license_plate, id FROM people WHERE name LIKE "Ernest" OR name LIKE "Russell";
-- Russell|322W7JE|514354
-- Ernest|94KL13X|686048

-- cross-reference bank accounts
SELECT name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id WHERE bank_accounts.account_number IN (SELECT account_number FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE transaction_type = "withdraw" AND atm_location = "Fifer Street" AND year = 2020 AND month = 7 AND day = 28));
-- Ernest
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

-- all indicators point to Ernets despite Russell being in the wrong place at the wrong time in some accounts

-- final destinations
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute);
-- London

-- find out who Ernest called to help him escape: (375) 555-8161
SELECT name FROM people WHERE phone_number = "(375) 555-8161";
-- Berthold