-- Keep a log of any SQL queries you execute as you solve the mystery.

--  the theft took place on July 28, 2021 and that it took place on Humphrey Street.
SELECT * FROM crime_scene_reports;
-- Find the duck theft
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2021 AND street = "Humphrey Street";
-- at 10:15 am in bakery. See the bakery logs
-- 1. witnes : Sometime within ten minutes of the theft...See security footage for cars that left the parking lot (10:20 = G412CB7, 10:21 = L93JTIZ, 10:23 = 322WW7JE, )
-- 2. witness : See ATM on Leggett Street earlier that day (deposit = 86363979)
-- 3. witness : flight out of FIftyville earliest tomorrow. Talked less then a minute flight id = 36( earliest at 8:20 = 4 New York City)

-- HOW TO SEE THE PASSENGERS OF THE FIRST FLIGHT FROM FIFTYVILLE;
SELECT * FROM passengers JOIN flights ON flights.id = passengers.flight_id WHERE flights.id = 36;


-- JOIN PEOPLE AND PHONE CALLS WITH DURATION < 60 DAY 28 MONT 7 YEAR 2021; ( PHONE NUMBER )
SELECT * FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE phone_calls.duration < 60 AND day = 28 AND month = 7 AND year = 2021;
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

-- Main suspects ( Sofia, Taylor, Kelsey and Bruce)
-- => FROM WITHES 1: Everyone of them was at the parking exit in bakery 10 minutes after theft.
-- ELIMINATE Tylor because he was at 10:35,,, Bruce was at 10:18 which is in the ten minutes after theft (10:15)
-- => FROM WITNES 2: Only Bruce and Taylor withdraw money that day from atm in Leggett Street.
SELECT * FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number JOIN people ON bank_accounts.person_id = people.id WHERE day = 28 AND month = 7 AND year  = 2021 AND atm_location = "Leggett Street";
-- => FROM witnes 3: Both of them where in the flight to New Your City in the earliest flight next day;
-- THE CALLS THAT DAY WITH DURATION LESS THAN A MINUTE
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;
-- => Everyone made a call less than 60 seconds

--=====> Bruce called Robin and the phone, duration was less than 60 he picked the earliest flight to New York City the day after theft, he also was at the bakery parking sport and withdraw some money from atm.
