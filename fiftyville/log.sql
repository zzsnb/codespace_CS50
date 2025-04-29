-- Keep a log of any SQL queries you execute as you solve the mystery.
/*All you know is that the theft took place on July 28, 2023 and that it took place on Humphrey Street.*/

.schema airports
--to dertermine the id  of thefiftyville airport
SELECT * FROM airports;
--id=8

--to check the crime scene reports
SELECT * FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
/*| 295 | 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
 Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |*/

-- To make the range smaller
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND
hour =10 AND minute > 15 AND activity = 'exit';
/*+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2023 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
+-----+------+-------+-----+------+--------+----------+---------------+*/

--to find their passport_number;
SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND
hour =10 AND minute > 15 AND activity = 'exit');

--to make the filght range smaller
SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2023 AND month >= 7 AND month <=9;
--find that there only July
--to make the range smaller
SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2023 AND month >= 7 AND day >=28 AND hour >= 10;
/*
+----+
| id |
+----+
| 1  |
| 6  |
| 7  |
| 8  |
| 10 |
| 11 |
| 17 |
| 18 |
| 23 |
| 31 |
| 34 |
| 35 |
| 44 |
| 53 |
| 54 |
+----+*/

SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2023 AND month >= 7 AND day >=28 AND hour >= 10) AND
passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND
hour =10 AND minute > 15 AND activity = 'exit'));

/*+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 11        | 8496433585      | 5D   |
| 18        | 3592750733      | 4C   |
| 54        | 3592750733      | 6C   |
+-----------+-----------------+------+*/

SELECT * FROM people WHERE passport_number IN (8496433585,3592750733,3592750733);
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
+--------+-------+----------------+-----------------+---------------+*/

SELECT * FROM flights WHERE id IN (18,54);

SELECT * FROM passengers WHERE passport_number = 3592750733;
--to except Diana

-- The theft is Luca
SELECT * FROM flights WHERE id = 11;
/*
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 11 | 8                 | 12                     | 2023 | 7     | 30  | 13   | 7      |
+----+-------------------+------------------------+------+-------+-----+------+--------+*/

SELECT * FROM airports WHERE id = 12;
/*
+----+--------------+-------------------------------------+-------+
| id | abbreviation |              full_name              | city  |
+----+--------------+-------------------------------------+-------+
| 12 | DEL          | Indira Gandhi International Airport | Delhi |
+----+--------------+-------------------------------------+-------+*/

SELECT * FROM bakery_security_logs WHERE license_plate = '4328GD8';
--to recheck

--miss some information before
SELECT * FROM interviews WHERE year =2023 AND month = 7 AND day = 28;
/*
| 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get
into a car in the bakery parking lot and drive away. If you have security footage from the bakery
parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street
and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery, they called someone who
talked to them for less than a minute. In the call, I heard the thief say that they were planning to
take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other
end of the phone to purchase the flight ticket. |*/

SELECT * FROM bank_accounts WHERE person_id = 467400;
/*+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 28500762       | 467400    | 2014          |
+----------------+-----------+---------------+*/

SELECT * FROM atm_transactions WHERE account_number = 28500762;
/*+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 7   | 28500762       | 2023 | 7     | 26  | Leggett Street | deposit          | 75     |
| 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+*/
--WITHDRAW!!!!

/*+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 57  | (389) 555-5198 | (368) 555-3561 | 2023 | 7     | 25  | 414      |
| 326 | (389) 555-5198 | (609) 555-5876 | 2023 | 7     | 29  | 397      |
+-----+----------------+----------------+------+-------+-----+----------+*/

--to find the accomplice
SELECT * FROM phone_calls WHERE receiver = '(389) 555-5198';

/*+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 227 | (544) 555-8087 | (389) 555-5198 | 2023 | 7     | 28  | 595      |
| 234 | (609) 555-5876 | (389) 555-5198 | 2023 | 7     | 28  | 60       |
| 408 | (609) 555-5876 | (389) 555-5198 | 2023 | 7     | 30  | 255      |
+-----+----------------+----------------+------+-------+-----+----------+*/

SELECT * FROM people WHERE phone_number = '(609) 555-5876';
--Kathryn

SELECT * FROM flights WHERE origin_airport_id = 8 AND day =28;--here get wrong
/*+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 1  | 8                 | 7                      | 2023 | 7     | 28  | 17   | 50     |
| 6  | 8                 | 5                      | 2023 | 7     | 28  | 13   | 49     |
| 17 | 8                 | 4                      | 2023 | 7     | 28  | 20   | 16     |
| 34 | 8                 | 5                      | 2023 | 7     | 28  | 17   | 20     |
| 35 | 8                 | 4                      | 2023 | 7     | 28  | 16   | 16     |
+----+-------------------+------------------------+------+-------+-----+------+--------+*/

SELECT * FROM passengers WHERE flight_id = 6;
/*+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 6         | 3835860232      | 9A   |
| 6         | 1618186613      | 2C   |
| 6         | 7179245843      | 3B   |
| 6         | 1682575122      | 4B   |
| 6         | 7597790505      | 5D   |
| 6         | 6128131458      | 6B   |
| 6         | 6264773605      | 7D   |
| 6         | 3642612721      | 8A   |
+-----------+-----------------+------+*/

SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6);
SELECT * FROM bakery_security_logs WHERE license_plate IN (SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6));
/*
| 259 | 2023 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 288 | 2023 | 7     | 28  | 17   | 15     | exit     | 13FNH73       |
*/

SELECT * FROM people WHERE license_plate = '13FNH73';
/*+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 745650 | Sophia | (027) 555-1068 | 3642612721      | 13FNH73       |
+--------+--------+----------------+-----------------+---------------+*/

SELECT * FROM bank_accounts WHERE person_id = 745650;

SELECT * FROM atm_transactions WHERE account_number = 42445987;
--find some wrong before

SELECT * FROM passengers WHERE flight_id = 36;
/*+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |
+-----------+-----------------+------+*/

SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

SELECT * FROM bakery_security_logs WHERE license_plate IN (SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36));
/*| 232 | 2023 | 7     | 28  | 8    | 23     | entrance | 94KL13X       |
| 237 | 2023 | 7     | 28  | 8    | 34     | entrance | 1106N58       |
| 243 | 2023 | 7     | 28  | 8    | 42     | entrance | 0NTHK55       |
| 254 | 2023 | 7     | 28  | 9    | 14     | entrance | 4328GD8       |
| 257 | 2023 | 7     | 28  | 9    | 28     | entrance | G412CB7       |
| 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2023 | 7     | 28  | 10   | 35     | exit     | 1106N58       |--this is impossible
*/
SELECT * FROM atm_transactions WHERE account_number IN (
SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE license_plate IN (SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36))
)));
/*| 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2023 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+*/
--还没查出来……果然正确答案的搜索路径就是如此恶心。。。
SELECT * FROM people WHERE license_plate = '1106N58';
--not Taylor

SELECT * FROM people WHERE license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE license_plate IN (SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36)));
/*+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+*/
SELECT * FROM bank_accounts WHERE account_number IN(
SELECT account_number FROM atm_transactions WHERE account_number IN (
SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE license_plate IN (SELECT license_plate FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36))
))));
--(395717,467400,686048)

SELECT * FROM phone_calls WHERE caller IN ('(826) 555-1652','(389) 555-5198','(367) 555-5533');
--| 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |is you ! Bruce!!!!!!! is you.......
--| 279 | (826) 555-1652 | (066) 555-9701 | 2023 | 7     | 28  | 55       |are you serious ? Kenny?

SELECT * FROM passengers WHERE passport_number = 5773159633;

SELECT * FROM flights WHERE id = 36;
/*+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+*/

SELECT * FROM airports WHERE id = 4;
/*+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+*/
--New York City
SELECT * FROM people WHERE phone_number ='(375) 555-8161';
--Robin


