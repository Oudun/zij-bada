DROP TABLE IF EXISTS `skyobject` ;

CREATE  TABLE IF NOT EXISTS `skyobject` (
  `constellations_code` VARCHAR(3) NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `greek` VARCHAR(8) NULL ,
  `magnitude` FLOAT NOT NULL ,
  `ra` DOUBLE NOT NULL ,
  `de` DOUBLE NOT NULL ,
  `is_northern` TINYINT(1) NOT NULL ,
  `color` VARCHAR(32) NULL ,
  `number` INT NOT NULL ,
  `is_star` TINYINT(1) NOT NULL)

