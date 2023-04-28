-- Keep a log of any SQL queries you execute as you solve the mystery.

--SCHEMAS
/*
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE courthouse_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
*/

select description from crime_scene_reports where month = 7 and day = 28 and street = 'Chamberlin Street';

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time —
-- each of their interview transcripts mentions the courthouse.

select * from interviews where month = 7 and day = 28;

/*| 161 | Ruth    | 2020 | 7     | 28  | Sometime within ten minutes of the theft,
I saw the thief get into a car in the courthouse parking lot and drive away.
If you have security footage from the courthouse parking lot, you might want to look for
cars that left the parking lot in that time frame.*/



/*| 162 | Eugene  | 2020 | 7     | 28  | I don't know the thief's name, but it was someone
I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the
ATM on Fifer Street and saw the thief there withdrawing some money.*/

/*| 163 | Raymond | 2020 | 7     | 28  | As the thief was leaving the courthouse,
they called someone who talked to them for less than a minute. In the call, I heard the thief
say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.*/


-- CREATE TABLE courthouse_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

select passport_number from people where license_plate in
(select license_plate from courthouse_security_logs where month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 35
and phone_number in (select caller from phone_calls where month = 7 and day = 28 and duration < 60);


select caller from phone_calls where month = 7 and day = 28 and duration < 60;
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 398010 | Roger   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 514354 | Russell | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Evelyn  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Ernest  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+
select * from flights where day = 29 and month = 7 ORDER BY hour;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2020 | 7     | 29  | 8    | 20     |
-- | 43 | 8                 | 1                      | 2020 | 7     | 29  | 9    | 30     |
-- | 23 | 8                 | 11                     | 2020 | 7     | 29  | 12   | 15     |
-- | 53 | 8                 | 9                      | 2020 | 7     | 29  | 15   | 20     |
-- | 18 | 8                 | 6                      | 2020 | 7     | 29  | 16   | 0      |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

select * from airports where id = 8;

select * from passengers where flight_id = 36 and passport_number in (select passport_number from people where license_plate in
(select license_plate from courthouse_security_logs where month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 35)
and phone_number in (select caller from phone_calls where month = 7 and day = 28 and duration < 60));

-- +-----------+-----------------+------+
-- | flight_id | passport_number | seat |
-- +-----------+-----------------+------+
-- | 36        | 1695452385      | 3B   |
-- | 36        | 5773159633      | 4A   |
-- | 36        | 8294398571      | 6C   |
-- +-----------+-----------------+------+

select * from people where passport_number in (1695452385,
5773159633,
8294398571)

-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 398010 | Roger  | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 560886 | Evelyn | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Ernest | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+--------+----------------+-----------------+---------------+

select * from atm_transactions where month = 7 and day = 28 and transaction_type = 'withdraw' and account_number = 49610011

select * from atm_transactions where month = 7 and day = 28 and transaction_type = 'withdraw' and hour <= 10

select * from bank_accounts where person_id in (398010,
560886,
686048)

select * from people where id = 686048

select * from phone_calls where caller = 'Ernest'

select * from phone_calls where month = 7 and day = 28 and duration < 60 and caller in
(SELECT phone_number from people where id = 686048);
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7     | 28  | 45       |
-- +-----+----------------+----------------+------+-------+-----+----------+
select name from people where phone_number = '(375) 555-8161'