SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';


-- -----------------------------------------------------
-- Table `locale`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `locale` ;

CREATE  TABLE IF NOT EXISTS `locale` (
  `id` INT NOT NULL ,
  `countryCode` VARCHAR(3) NOT NULL ,
  `langCode` VARCHAR(2) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `names`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `names` ;

CREATE  TABLE IF NOT EXISTS `names` (
  `name_code` VARCHAR(64) NOT NULL ,
  PRIMARY KEY (`name_code`) ,
  UNIQUE INDEX `name_code_UNIQUE` (`name_code` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `countries`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `countries` ;

CREATE  TABLE IF NOT EXISTS `countries` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `border_length` INT NOT NULL DEFAULT 0 ,
  `area` BIGINT(20) NOT NULL DEFAULT 0 ,
  INDEX `fk_countries_names1_idx` (`names_name_code` ASC) ,
  UNIQUE INDEX `names_name_code_UNIQUE` (`names_name_code` ASC) ,
  PRIMARY KEY (`id`) ,
  CONSTRAINT `fk_countries_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `cities`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cities` ;

CREATE  TABLE IF NOT EXISTS `cities` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `longitude` FLOAT NOT NULL ,
  `latitude` FLOAT NOT NULL ,
  `population` INT NOT NULL ,
  `countries_name` VARCHAR(64) NOT NULL ,
  INDEX `fk_cities_names1_idx` (`names_name_code` ASC) ,
  PRIMARY KEY (`id`) ,
  CONSTRAINT `fk_cities_names1`
    FOREIGN KEY (`names_name_code` )
    REFERENCES `names` (`name_code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `constellations`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `constellations` ;

CREATE  TABLE IF NOT EXISTS `constellations` (
  `names_name_code` VARCHAR(64) NOT NULL ,
  `code` VARCHAR(3) NOT NULL ,
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
DROP TABLE IF EXISTS `skyobject` ;

CREATE  TABLE IF NOT EXISTS `skyobject` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT ,
  `constellations_code` VARCHAR(3) NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `greek` VARCHAR(8) NULL ,
  `magnitude` FLOAT NOT NULL ,
  `ra` DOUBLE NOT NULL ,
  `de` DOUBLE NOT NULL ,
  `is_northern` TINYINT(1) NOT NULL ,
  `color` VARCHAR(16) NULL ,
  `number` INT NOT NULL ,
  `is_star` TINYINT(1) NOT NULL ,
  INDEX `fk_skyobject_constellations1_idx` (`constellations_code` ASC) ,
  INDEX `fk_skyobject_names1_idx` (`names_name_code` ASC) ,
  PRIMARY KEY (`id`) ,
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
-- Table `constellation_border`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `constellation_border` ;

CREATE  TABLE IF NOT EXISTS `constellation_border` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT ,
  `ra` DOUBLE NULL ,
  `de` DOUBLE NULL ,
  `order` INT NULL ,
  `constellations_code` VARCHAR(3) NOT NULL ,
  INDEX `fk_constellationBorder_constellations1_idx` (`constellations_code` ASC) ,
  PRIMARY KEY (`id`) ,
  CONSTRAINT `fk_constellationBorder_constellations1`
    FOREIGN KEY (`constellations_code` )
    REFERENCES `constellations` (`code` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `localized_name`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `localized_name` ;

CREATE  TABLE IF NOT EXISTS `localized_name` (
  `locale_id` INT NOT NULL ,
  `names_name_code` VARCHAR(64) NOT NULL ,
  `localized_name` VARCHAR(128) NULL ,
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT ,
  INDEX `fk_localized_name_locale1_idx` (`locale_id` ASC) ,
  INDEX `fk_localized_name_names1_idx` (`names_name_code` ASC) ,
  PRIMARY KEY (`id`) ,
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
DROP TABLE IF EXISTS `app_resources` ;

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
