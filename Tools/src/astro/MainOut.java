package astro;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Locale;

/**
 * Created by:          $Author:: ddreval
 * Creation time:       $Date:: 2012-11-13 17:36
 * Last modified by:    $Author::                   $
 * Modification time:   $Date::                     $
 * File revision:       $Rev::                      $
 */
public class MainOut {

    public static void main (String[] args) throws Exception {

        Class.forName("org.sqlite.JDBC");

        Connection connection = DriverManager.getConnection("jdbc:sqlite:stars.db");
        Statement statement = connection.createStatement();
        statement.setQueryTimeout(30);  // set timeout to 30 sec.
//        //ResultSet rs = statement.executeQuery("select * from stars");
//        ResultSet rs = statement.executeQuery("select * from stars where constellation='Ori'");
//        while (rs.next()) {
//            System.out.println(String.format(Locale.US, "Name %s (%s) magnitude %f RA:%f DEC:%f %d hemisphere",
//                    rs.getString("greek"),
//                    rs.getString("constellation"),
//                    rs.getFloat("magnitude"),
//                    rs.getFloat("ra"),
//                    rs.getFloat("dec"),
//                    rs.getInt("northern")));
//        }


        ResultSet rs = statement.executeQuery("select count(*) from stars");
        while (rs.next()) {
            System.out.println(rs.getInt(1));
        }


    }

//    "greek string, " +
//    "constellation string, " +
//    "magnitude float, " +
//    "ra float, " +
//    "dec float, " +
//    "northern int)");

}
