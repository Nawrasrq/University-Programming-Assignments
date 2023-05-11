-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Apr 16, 2022 at 12:45 AM
-- Server version: 5.7.36
-- PHP Version: 7.4.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `project`
--
CREATE DATABASE IF NOT EXISTS `project` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `project`;

-- --------------------------------------------------------

--
-- Table structure for table `apart`
--

DROP TABLE IF EXISTS `apart`;
CREATE TABLE IF NOT EXISTS `apart` (
  `user_id` int(11) NOT NULL,
  `RSO_id` int(11) NOT NULL,
  PRIMARY KEY (`user_id`,`RSO_id`),
  KEY `RSO_id` (`RSO_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `apart`
--

INSERT INTO `apart` (`user_id`, `RSO_id`) VALUES
(3, 1),
(4, 1),
(8, 1),
(1, 2),
(2, 2),
(3, 2),
(6, 2),
(7, 2),
(8, 2),
(9, 2),
(10, 2),
(12, 3),
(18, 3),
(12, 4),
(13, 4),
(14, 4),
(15, 4),
(17, 4),
(18, 4),
(21, 10);

-- --------------------------------------------------------

--
-- Table structure for table `comments`
--

DROP TABLE IF EXISTS `comments`;
CREATE TABLE IF NOT EXISTS `comments` (
  `comment_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `event_id` int(11) NOT NULL,
  `text` text NOT NULL,
  `rating` int(11) NOT NULL,
  `timestamp` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`comment_id`),
  KEY `user_id` (`user_id`),
  KEY `event_id` (`event_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `comments`
--

INSERT INTO `comments` (`comment_id`, `user_id`, `event_id`, `text`, `rating`, `timestamp`) VALUES
(1, 4, 1, 'Got a lot of studying done!', 5, '2022-04-21 18:52:04'),
(2, 8, 2, 'Drew some great stuff!', 4, '2022-04-20 18:52:04'),
(3, 4, 5, 'I don\'t think art is my thing', 2, '2022-04-26 18:54:32');

-- --------------------------------------------------------

--
-- Table structure for table `createevent`
--

DROP TABLE IF EXISTS `createevent`;
CREATE TABLE IF NOT EXISTS `createevent` (
  `event_id` int(11) NOT NULL,
  `RSO_id` int(11) NOT NULL,
  PRIMARY KEY (`event_id`,`RSO_id`),
  KEY `RSO_id` (`RSO_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `createevent`
--

INSERT INTO `createevent` (`event_id`, `RSO_id`) VALUES
(2, 2),
(10, 4);

-- --------------------------------------------------------

--
-- Table structure for table `event`
--

DROP TABLE IF EXISTS `event`;
CREATE TABLE IF NOT EXISTS `event` (
  `event_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` char(50) NOT NULL,
  `category` char(50) DEFAULT NULL,
  `description` text,
  `email` char(50) DEFAULT NULL,
  `phone` char(50) DEFAULT NULL,
  `date_time` datetime DEFAULT NULL,
  `location` char(50) DEFAULT NULL,
  `school` varchar(50) NOT NULL,
  PRIMARY KEY (`event_id`),
  UNIQUE KEY `date_time` (`date_time`,`location`),
  KEY `location` (`location`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `event`
--

INSERT INTO `event` (`event_id`, `name`, `category`, `description`, `email`, `phone`, `date_time`, `location`, `school`) VALUES
(1, 'Study Time', 'Public', 'Come and study with fellow students', 'arthur@knights.ucf.edu', '1234567891', '2022-04-20 18:30:17', '12800 Gemini Blvd S, Orlando, FL 32816, USA', 'knights.ucf.edu'),
(2, 'Art Time', 'RSO', NULL, 'tiny@knights.ucf.edu', '4382375647', '2022-04-19 18:30:17', '115 Boston Ave, Altamonte Springs', 'knights.ucf.edu'),
(5, 'Art Review', 'Private', NULL, 'tiny@knights.ucf.edu', '345-234-1000', '2022-04-29 18:37:31', '1800 Meadowgold Ln', 'knights.ucf.edu'),
(6, 'Party Time', 'Public', NULL, 'sammy@valencia.edu', '853-999-1212', '2022-04-15 22:37:31', 'JPX6+QH Casselberry', 'valencia.edu'),
(7, 'College Tours', 'Public', 'Tour the college', 'camila@valencia.edu', '321-332-8912', '2022-04-25 22:47:45', '5471 Lily St, Orlando, FL 32811, USA', 'valencia.edu'),
(10, 'Party Party', 'RSO', 'Party time, RSO members only', 'sammy@valencia.edu', '999-999-9999', '2022-04-21 19:15:25', '957 Barbados Ave', 'valencia.edu'),
(11, 'Art Review at valencia', 'Private', NULL, 'tiny@valencia.edu', '345-234-1000', '2022-04-15 18:37:31', '1800 Meadowgold Ln', 'valencia.edu'),
(13, 'Art Review at valencia 2', 'Private', NULL, 'tiny@valencia.edu', '345-234-1000', '2022-04-23 18:37:31', '1800 Meadowgold Ln', 'valencia.edu');

-- --------------------------------------------------------

--
-- Table structure for table `location`
--

DROP TABLE IF EXISTS `location`;
CREATE TABLE IF NOT EXISTS `location` (
  `address` char(50) NOT NULL,
  `longitude` float NOT NULL,
  `latitude` float NOT NULL,
  PRIMARY KEY (`address`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `location`
--

INSERT INTO `location` (`address`, `longitude`, `latitude`) VALUES
('115 Boston Ave, Altamonte Springs', -81.3694, 28.6613),
('12800 Gemini Blvd S, Orlando, FL 32816, USA', -81.1979, 28.5947),
('1800 Meadowgold Ln', -81.2772, 28.6325),
('5471 Lily St, Orlando, FL 32811, USA', -81.4526, 28.5231),
('957 Barbados Ave', -81.2229, 28.5585),
('JPX6+QH Casselberry', -81.2872, 28.6481);

-- --------------------------------------------------------

--
-- Table structure for table `public_request`
--

DROP TABLE IF EXISTS `public_request`;
CREATE TABLE IF NOT EXISTS `public_request` (
  `event_id` int(11) NOT NULL,
  `uni_id` int(11) NOT NULL,
  UNIQUE KEY `event_id` (`event_id`,`uni_id`),
  KEY `uni_id` (`uni_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `public_request`
--

INSERT INTO `public_request` (`event_id`, `uni_id`) VALUES
(1, 1),
(6, 2),
(7, 2);

-- --------------------------------------------------------

--
-- Table structure for table `rso`
--

DROP TABLE IF EXISTS `rso`;
CREATE TABLE IF NOT EXISTS `rso` (
  `RSO_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `name` char(50) DEFAULT NULL,
  `status` varchar(20) NOT NULL DEFAULT 'Inactive',
  `description` text,
  `school` varchar(50) NOT NULL,
  PRIMARY KEY (`RSO_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `rso`
--

INSERT INTO `rso` (`RSO_id`, `user_id`, `name`, `status`, `description`, `school`) VALUES
(1, 3, 'Super Science Club', 'Inactive', 'We study super science', 'knights.ucf.edu'),
(2, 7, 'Super Art Club', 'Active', 'We create super art', 'knights.ucf.edu'),
(3, 18, 'Super Geology Club', 'Inactive', 'We study super rocks', 'valencia.edu'),
(4, 13, 'Super Party Fun Time', 'Active', 'We have super fun', 'valencia.edu'),
(10, 21, 'Test Club', 'Inactive', 'For testing the database', 'valencia.edu');

-- --------------------------------------------------------

--
-- Table structure for table `superadmin`
--

DROP TABLE IF EXISTS `superadmin`;
CREATE TABLE IF NOT EXISTS `superadmin` (
  `user_id` int(11) NOT NULL,
  `uni_id` int(11) NOT NULL,
  UNIQUE KEY `user_id` (`user_id`,`uni_id`),
  KEY `uni_id` (`uni_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `superadmin`
--

INSERT INTO `superadmin` (`user_id`, `uni_id`) VALUES
(5, 1),
(11, 2);

-- --------------------------------------------------------

--
-- Table structure for table `uni_pro`
--

DROP TABLE IF EXISTS `uni_pro`;
CREATE TABLE IF NOT EXISTS `uni_pro` (
  `uni_id` int(11) NOT NULL AUTO_INCREMENT,
  `school` varchar(50) NOT NULL,
  `description` varchar(100) NOT NULL,
  `location` varchar(50) NOT NULL,
  `number of students` int(11) NOT NULL,
  PRIMARY KEY (`uni_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `uni_pro`
--

INSERT INTO `uni_pro` (`uni_id`, `school`, `description`, `location`, `number of students`) VALUES
(1, 'knights.ucf.edu', 'University of Central Florida', '4000 Central Florida Blvd', 70000),
(2, 'valencia.edu', 'Valencia College', '701 N Econlockhatchee Trl', 10000);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE IF NOT EXISTS `user` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(50) NOT NULL DEFAULT '',
  `school` varchar(50) DEFAULT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL DEFAULT '',
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`user_id`, `email`, `school`, `username`, `password`) VALUES
(1, 'matt@knights.ucf.edu', 'knights.ucf.edu', 'mattypatty', 'marc'),
(2, 'kevin@knights.ucf.edu', 'knights.ucf.edu', 'kev', 'kekkke'),
(3, 'will@knights.ucf.edu', 'knights.ucf.edu', 'robobo', 'gear'),
(4, 'mike@knights.ucf.edu', 'knights.ucf.edu', 'sneed', 'machine'),
(5, 'arthur@knights.ucf.edu', 'knights.ucf.edu', 'arthus', 'monk'),
(6, 'techies@knights.ucf.edu', 'knights.ucf.edu', 'techies', 'boomboom'),
(7, 'tiny@knights.ucf.edu', 'knights.ucf.edu', 'tiny', 'rocks'),
(8, 'gobby@knights.ucf.edu', 'knights.ucf.edu', 'gobby', 'goblin'),
(9, 'steven@knights.ucf.edu', 'knights.ucf.edu', 'steve', 'steamy'),
(10, 'scrumpy@knights.ucf.edu', 'knights.ucf.edu', 'scrumps', 'scrum'),
(11, 'camila@valencia.edu', 'valencia.edu', 'cammy', 'cam'),
(12, 'hector@valencia.edu', 'valencia.edu', 'hector', 'himy'),
(13, 'sammy@valencia.edu', 'valencia.edu', 'samson', 'son'),
(14, 'DK@valencia.edu', 'valencia.edu', 'DonkeyKong', 'DK'),
(15, 'lefty@valencia.edu', 'valencia.edu', 'lefty', 'righty'),
(16, 'momo@valencia.edu', 'valencia.edu', 'momo', 'lemons'),
(17, 'lemonBoy@valencia.edu', 'valencia.edu', 'lemonBoy', 'citrus'),
(18, 'kekleon@valencia.edu', 'valencia.edu', 'kekleon', 'pokemon'),
(19, 'leo@valencia.edu', 'valencia.edu', 'lion', 'rawr'),
(20, 'croak@valencia.edu', 'valencia.edu', 'frog', 'boy'),
(21, 'test@valencia.edu', 'valencia.edu', 'test', 'pas'),
(22, 'test2@knights.ucf.edu', 'knights.ucf.edu', 'test2', 'pas');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `apart`
--
ALTER TABLE `apart`
  ADD CONSTRAINT `RSO_id` FOREIGN KEY (`RSO_id`) REFERENCES `rso` (`RSO_id`),
  ADD CONSTRAINT `user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`);

--
-- Constraints for table `comments`
--
ALTER TABLE `comments`
  ADD CONSTRAINT `comments_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`),
  ADD CONSTRAINT `comments_ibfk_2` FOREIGN KEY (`event_id`) REFERENCES `event` (`event_id`);

--
-- Constraints for table `createevent`
--
ALTER TABLE `createevent`
  ADD CONSTRAINT `createevent_ibfk_1` FOREIGN KEY (`RSO_id`) REFERENCES `rso` (`RSO_id`),
  ADD CONSTRAINT `createevent_ibfk_2` FOREIGN KEY (`event_id`) REFERENCES `event` (`event_id`);

--
-- Constraints for table `event`
--
ALTER TABLE `event`
  ADD CONSTRAINT `event_ibfk_1` FOREIGN KEY (`location`) REFERENCES `location` (`address`);

--
-- Constraints for table `public_request`
--
ALTER TABLE `public_request`
  ADD CONSTRAINT `public_request_ibfk_1` FOREIGN KEY (`event_id`) REFERENCES `event` (`event_id`),
  ADD CONSTRAINT `public_request_ibfk_2` FOREIGN KEY (`uni_id`) REFERENCES `uni_pro` (`uni_id`);

--
-- Constraints for table `superadmin`
--
ALTER TABLE `superadmin`
  ADD CONSTRAINT `superadmin_ibfk_1` FOREIGN KEY (`uni_id`) REFERENCES `uni_pro` (`uni_id`),
  ADD CONSTRAINT `superadmin_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
