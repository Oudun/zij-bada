package astro;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

/**
 * Created with IntelliJ IDEA.
 * User: ddreval
 * Date: 29.03.13
 * Time: 14:13
 * To change this template use File | Settings | File Templates.
 */
public class CountryLocation {

    static Connection c;
    static PreparedStatement INSERT_CITY_STAT;
    static PreparedStatement INSERT_COUNTRY_STAT;
    static PreparedStatement INSERT_NAME_STAT;

//    CREATE  TABLE IF NOT EXISTS `cities` (
//            `longitude` FLOAT NOT NULL ,
//            `latitude` FLOAT NOT NULL ,
//            `population` INT NOT NULL ,
//            `countries_name` VARCHAR(64) NOT NULL ,
//    `names_name_code` VARCHAR(64) NOT NULL ,

//    CREATE  TABLE IF NOT EXISTS `countries` (
//            `name` VARCHAR(64) NOT NULL ,
//    `border_length` INT NOT NULL ,
//            `names_name_code` VARCHAR(64) NOT NULL ,

//CREATE  TABLE IF NOT EXISTS `names` (
//        `name_code` VARCHAR(64) NOT NULL ,




    static {
        try {
            Class.forName("org.gjt.mm.mysql.Driver");
            c = DriverManager.getConnection("jdbc:mysql://localhost/astro", "root", "admin");
            INSERT_CITY_STAT = c.prepareStatement("INSERT INTO cities VALUES (NULL, ?, ? , ?, ?, ?)");
            INSERT_COUNTRY_STAT = c.prepareStatement("INSERT INTO countries VALUES (NULL, ?, 0, 0)");
            INSERT_NAME_STAT = c.prepareStatement("INSERT INTO names VALUES (?)");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(0);
        }
    }

    public static void storeCity(String[] parts) throws Exception {
//        try {
        System.out.println("Storing " + parts[6]);
            INSERT_CITY_STAT.setString(1, parts[1]);
            INSERT_CITY_STAT.setFloat(2, Float.parseFloat(parts[6]));
            INSERT_CITY_STAT.setFloat(3, Float.parseFloat(parts[7]));
            INSERT_CITY_STAT.setInt(4, Integer.parseInt(parts[5]));
            INSERT_CITY_STAT.setString(5, parts[8]);
            INSERT_CITY_STAT.execute();
//        } catch (Exception e) {
//            ;
//        }
    }

    public static void storeCountry(String[] parts) throws Exception {
        try {
            INSERT_COUNTRY_STAT.setString(1, parts[8]);
            INSERT_COUNTRY_STAT.execute();
        } catch (Exception e) {
            ;
        }
    }

    public static void storeCountryName(String[] parts) throws Exception {
        try {
            INSERT_NAME_STAT.setString(1, parts[8]);
            INSERT_NAME_STAT.execute();
        } catch (Exception e) {
            ;
        }
    }

    public static void storeCityName(String[] parts) throws Exception  {
        try {
            INSERT_NAME_STAT.setString(1, parts[1]);
            INSERT_NAME_STAT.execute();
        } catch (Exception e) {
            ;
        }
    }


    public static void main (String args[]) throws Exception {

        File dataFile = new File("city_location.txt");
        BufferedReader br = new BufferedReader(new FileReader(dataFile));
        int counter = 0;
        while (br.ready()) {
            String line = br.readLine();
            String[] parts = line.split("\t");
            try {
                int population = Integer.parseInt(parts[5]);
                if (parts[6].trim().length()>0) {
                    System.out.println(counter + "\t"  + parts[1]+"\t\t\t"+parts[6]+"\t"+parts[7]+"\t"+parts[8]);
                    //storeParts(parts);
                    storeCountryName(parts);
                    storeCountry(parts);
                    storeCityName(parts);
                    storeCity(parts);
                    counter++;
                }
            } catch (ArrayIndexOutOfBoundsException e) {
                ;
            } catch (NumberFormatException e) {
                ;
            }
        }

    }


}

// 0 Unique identification number of the geographical object
// 1 name of the geographical entity (english name, if available)
// 2 alternative names
// 3 original names in greek, cyrillic or arabic
// 4 type of geografical object (e.g. country, locality etc)
// 5 current population
// 6 latitude (for places)
// 7 longitude (for places)
// 8 parent country
// 9 parent administrative division of first level
// 10 parent administrative division of second level
// 11 parent administrative division of third level


// Coordinates translated as:
// São Paulo -2353	-4663 to 23°33′S 46°38′W
// Moscow     5575	3762 to 55°45′N 37°37′E