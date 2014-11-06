SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';


-- -----------------------------------------------------
-- Table `locale`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `locale` (
  `id` INT NOT NULL ,
  `countryCode` VARCHAR(3) NOT NULL ,
  `langCode` VARCHAR(2) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `names`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `names` (
  `name_code` VARCHAR(64) NOT NULL ,
  `namescol` VARCHAR(45) NULL ,
  PRIMARY KEY (`name_code`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `countries`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `countries` (
  `name` VARCHAR(64) NOT NULL ,
  `border_length` INT NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  PRIMARY KEY (`name`) ,
  INDEX `fk_countries_names1_idx` (`names_name_code` ASC) ,
  CONSTRAINT `fk_countries_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `cities`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `cities` (
  `longitude` FLOAT NOT NULL ,
  `latitude` FLOAT NOT NULL ,
  `population` INT NOT NULL ,
  `countries_name` VARCHAR(64) NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  INDEX `fk_cities_countries_idx` (`countries_name` ASC) ,
  INDEX `fk_cities_names1_idx` (`names_name_code` ASC) ,
  CONSTRAINT `fk_cities_countries`
    FOREIGN KEY (`countries_name` )
    REFERENCES `countries` (`name` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_cities_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `constellations`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `constellations` (
  `code` VARCHAR(3) NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  PRIMARY KEY (`code`) ,
  INDEX `fk_constellations_names1_idx` (`names_name_code` ASC) ,
  CONSTRAINT `fk_constellations_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `skyobject`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `skyobject` (
  `greek` VARCHAR(8) NULL ,
  `magnitude` FLOAT NOT NULL ,
  `ra` DOUBLE NOT NULL ,
  `de` DOUBLE NOT NULL ,
  `is_northern` TINYINT(1) NOT NULL ,
  `constellations_code` VARCHAR(3) NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `color` VARCHAR(16) NULL ,
  `number` INT NOT NULL ,
  `is_star` TINYINT(1) NOT NULL ,
  PRIMARY KEY (`greek`) ,
  INDEX `fk_skyobject_constellations1_idx` (`constellations_code` ASC) ,
  INDEX `fk_skyobject_names1_idx` (`names_name_code` ASC) ,
  CONSTRAINT `fk_skyobject_constellations1`
    FOREIGN KEY (`constellations_code` )
    REFERENCES `constellations` (`code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_skyobject_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `constellationBorder`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `constellationBorder` (
  `ra` DOUBLE NULL ,
  `de` DOUBLE NULL ,
  `order` INT NULL ,
  `constellations_code` VARCHAR(3) NOT NULL ,
  INDEX `fk_constellationBorder_constellations1_idx` (`constellations_code` ASC) ,
  CONSTRAINT `fk_constellationBorder_constellations1`
    FOREIGN KEY (`constellations_code` )
    REFERENCES `constellations` (`code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `localized_name`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `localized_name` (
  `locale_id` INT NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `localized_name` VARCHAR(128) NULL ,
  INDEX `fk_localized_name_locale1_idx` (`locale_id` ASC) ,
  INDEX `fk_localized_name_names1_idx` (`names_name_code` ASC) ,
  CONSTRAINT `fk_localized_name_locale1`
    FOREIGN KEY (`locale_id` )
    REFERENCES `locale` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_localized_name_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `app_resources`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `app_resources` (
  `code` VARCHAR(16) NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  PRIMARY KEY (`code`) ,
  INDEX `fk_app_resources_names1_idx` (`names_name_code` ASC) ,
  CONSTRAINT `fk_app_resources_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
