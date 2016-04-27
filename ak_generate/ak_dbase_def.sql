
0|display_name|varchar(64)|1||0
1|name|varchar(64)|1||0
2|local_site_id|integer|0||0
3|incoming_request_count|integer|0||0
4|invite_only|bool|1||0
5|id|integer|1||1
6|mailing_list|varchar(75)|1||0
7|visible|bool|1||0
PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION; 
CREATE TABLE "reviews_group"("display_name" varchar(64) NOT NULL, "name" varchar(64) NOT NULL, "local_site_id" integer NULL, "incoming_request_count" integer NULL, "invite_only" bool NOT NULL, "id" integer NOT NULL UNIQUE PRIMARY KEY, "mailing_list" varchar(75) NOT NULL, "visible" bool NOT NULL);
INSERT INTO "reviews_group" VALUES('Developers','developers',NULL,127,0,1,'',1);
INSERT INTO "reviews_group" VALUES('Testers','testers',NULL,2,0,2,'',1);
INSERT INTO "reviews_group" VALUES('QA','qa',NULL,1,0,3,'',1);
INSERT INTO "reviews_group" VALUES('Release Engineers','releng',NULL,7,0,4,'',1);
INSERT INTO "reviews_group" VALUES('Managers','mgrs',NULL,1,0,5,'',1);
COMMIT;





----------------------------------------




BEGIN TRANSACTION;
CREATE TABLE coffees (
  id INTEGER PRIMARY KEY,
  coffee_name TEXT NOT NULL,
  price REAL NOT NULL
);
INSERT INTO "coffees" VALUES(1,'Colombian',7.99);
INSERT INTO "coffees" VALUES(2,'French_Roast',8.99);
INSERT INTO "coffees" VALUES(3,'Espresso',9.99);
INSERT INTO "coffees" VALUES(4,'Colombian_Decaf',8.99);
INSERT INTO "coffees" VALUES(5,'French_Roast_Decaf',9.99);
COMMIT;


----------------------------------------------------------------------



CREATE DATABASE IF NOT EXISTS `db_name`;
USE `db_name`;

CREATE TABLE IF NOT EXISTS `customers` (
  `id` int(10) unsigned NOT NULL,
  `f_name` varchar(50) DEFAULT NULL,
  `l_name` varchar(50) DEFAULT NULL,
  `company_name` varchar(200) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `phone` varchar(25) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `customers` (`id`, `f_name`, `l_name`, `company_name`, `email`, `phone`) VALUES
    ...
    ...
    
---------------------



-- Database schema
CREATE TABLE artist(
  artistid    INTEGER PRIMARY KEY, 
  artistname  TEXT
);
CREATE TABLE track(
  trackid     INTEGER,
  trackname   TEXT, 
  trackartist INTEGER REFERENCES artist(artistid) ON UPDATE CASCADE
);


--------------------------------------


