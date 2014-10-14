package astro;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.text.MessageFormat;
import java.util.Locale;

/**
 * Created by:          $Author:: ddreval
 * Creation time:       $Date:: 2012-11-13 15:32
 * Last modified by:    $Author::                   $
 * Modification time:   $Date::                     $
 * File revision:       $Rev::                      $
 */
public class MainInDb {

    private static Statement statement;

    private static void initDatabase() throws Exception {
//        Class.forName("org.sqlite.JDBC");
//        Connection connection = DriverManager.getConnection("jdbc:sqlite:stars.db");
//        statement = connection.createStatement();
//        statement.setQueryTimeout(30);  // set timeout to 30 sec.
//        statement.executeUpdate("drop table if exists stars");
//        statement.executeUpdate("drop table if exists boundaries");
//        statement.executeUpdate("create table stars (" +
//                "greek string, " +
//                "constellation string, " +
//                "magnitude float, " +
//                "ra float, " +
//                "dec float, " +
//                "northern int)");
//        statement.executeUpdate("create table boundaries (" +
//                "constellation string, " +
//                "ra float, " +
//                "dec float, " +
//                "northern int)");

        Class.forName("org.gjt.mm.mysql.Driver");
        Connection c = DriverManager.getConnection("jdbc:mysql://localhost/astro", "root", "admin");
        statement = c.createStatement();

    }

    public static void main (String[] args) throws Exception {

        initDatabase();


        parseCatalog("catalogue-1");
        parseCatalog("catalogue-2");
        parseCatalog("catalogue-3");
        parseCatalog("catalogue-4");
        parseCatalog("catalogue-5");
        parseCatalog("catalogue-6");

//        parseBoundaries();

    }

    private static void parseBoundaries() throws Exception {
        MessageFormat BOUNDARY_STRING_FORMAT =
                new MessageFormat("{0} {1} {2}|{3}|{4}"); //"22 57 51.6729| 35.1682358|AND"
        File boundDir = new File("boundaries");
        for (File boundFile : boundDir.listFiles()) {
            BufferedReader br = new BufferedReader(new FileReader(boundFile));
            while (br.ready()) {
                try {
                    String boundaryString = br.readLine();
                    Object[] parts = BOUNDARY_STRING_FORMAT.parse(boundaryString);
                    float RA = Float.parseFloat((String)parts[0])
                            + Float.parseFloat((String)parts[1])/60
                            + Float.parseFloat((String)parts[2])/3600;
                    float DE = Float.parseFloat(((String)parts[3]).trim());
                    int northern = DE > 0 ? 1 : 0;
                    if (northern == 0) {
                        DE = -DE;
                    }
                    String constellation = (String)parts[4];
//                    if (constellation!=null && constellation.trim().length() > 0) {
//                        constellation = "CONST_" + constellation.trim();
//                    }
                    System.out.println(String.format("Boundary of %s : RA %f DE %f", constellation, RA, DE));
                    addBound((String)parts[4], RA, DE, northern);
                } catch (Exception e) {
                    e.printStackTrace();
                    System.out.println(boundFile.getAbsolutePath());
                }
            }
        }
    }

    private static void parseCatalog(String catalog) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(catalog));
        while(br.ready()) {
            String line = br.readLine();

            int harvardNumber = Integer.parseInt(line.substring(0,4).trim());
            String specterType = line.substring(128,147).trim();

            String name = line.substring(5,14);
            String greek = line.substring(7,10);
            String constellation = line.substring(11,14);
//            if (constellation!=null && constellation.trim().length() > 0) {
//                constellation = "CONST_" + constellation.trim();
//            }
            String drapperName = line.substring(26, 31);
            float magnitude = Float.parseFloat(line.substring(102, 107)); // to float
            String sign = line.substring(83,84);

            // Right Ascention
            String rah = line.substring(75, 77);
            String ram = line.substring(77, 79);
            String ras = line.substring(79, 81);
            float ra = Float.parseFloat(rah) + Float.parseFloat(ram)/60 + Float.parseFloat(ras)/3600;

            // Declination
            String deh = line.substring(84, 86);
            String dem = line.substring(86, 88);
            String des = line.substring(88, 90);
            float dec = Float.parseFloat(deh) + Float.parseFloat(dem)/60 + Float.parseFloat(des)/3600;

            System.out.println(String.format(Locale.US, "Number %d. Name %s (%s) magnitude %f RA:%f DEC:%f %s hemisphere. Specter type %s",
                    harvardNumber, greek, constellation.toUpperCase(), magnitude, ra, dec, sign.equals("+")?"Northern":"Southern", specterType));

//            if (greek.trim().length()>0&&constellation.trim().length()>0) {
                addStar(greek, constellation.toUpperCase(), magnitude, ra, dec, sign.equals("+")?1:0, harvardNumber, specterType);
//            }

        }
        br.close();
    }


    private static void addStar(String gr, String cns, float mag, float ra, float dec, int north, int number, String specterType) throws Exception {
//        statement.executeUpdate(
//                String.format(Locale.US, "insert into stars values('%s', '%s', %f, %f, %f, %d)", gr, cns, mag, ra, dec, north));


//        `constellations_code` VARCHAR(3) NOT NULL ,
//        `names_name_code` VARCHAR(64) NOT NULL ,
//        `greek` VARCHAR(8) NULL ,
//        `magnitude` FLOAT NOT NULL ,
//        `ra` DOUBLE NOT NULL ,
//        `de` DOUBLE NOT NULL ,
//        `is_northern` TINYINT(1) NOT NULL ,
//        `color` VARCHAR(16) NULL ,
//        `number` INT NOT NULL ,
//        `is_star` TINYINT(1) NOT NULL ,

        String str = String.format(Locale.US, "insert into skyobject values('%s', '%s','%s', %f, %f, %f, %d, '%s', %d, %d)",
                cns, "NAME", gr, mag, ra, dec, north, specterType, number, 1);
        statement.executeUpdate(
                String.format(Locale.US, "insert into skyobject values('%s', '%s','%s', %f, %f, %f, %d, '%s', %d, %d)",
                        cns, "NAME", gr, mag, ra, dec, north, specterType, number, 1));

    }

    private static void addBound(String cns, float ra, float dec, int north) throws Exception {
        statement.executeUpdate(
                String.format(Locale.US, "insert into boundaries values('%s', %f, %f, %d)", cns, ra, dec, north));
    }

}

//    AppLog("Getting next star2%d", counter);
//   	line.SubString(5, 9, substr1);
//   	substr1.Trim();
//   	nextObject->setName(substr1);
//   	line.SubString(25, 6, substr1);
//   	substr1.Trim();
//   	nextObject->setDraperName(substr1);
//   	line.SubString(102, 5, substr1);
//   	substr1.Trim();
//   	nextObject->setMagnitude(substr1);
//   	line.SubString(83, 1, substr1);
//   	nextObject->setSign(substr1.Equals("+", false));
//   	nextObject->setDraperName(substr1);

//   	line.SubString(75, 2, substr1);
//   	line.SubString(77, 2, substr2);
//   	line.SubString(79, 4, substr3);
//   	nextObject->setRA(substr1, substr2, substr3);

//   	line.SubString(84, 2, substr1 );
//   	line.SubString(86, 2, substr2 );
//   	line.SubString(88, 2, substr3 );
//   	nextObject->setDE(substr1, substr2, substr3);

