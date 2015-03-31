package astro;

import java.sql.*;
import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: ddreval
 * Date: 05.04.13
 * Time: 15:02
 * To change this template use File | Settings | File Templates.
 */
public class CityOnNet {


    static Statement sqLiteStatement;

    private static void initSqLite() throws Exception {
        Class.forName("org.sqlite.JDBC");
        Connection connection = DriverManager.getConnection("jdbc:sqlite:stars.db");
        sqLiteStatement = connection.createStatement();
        sqLiteStatement.setQueryTimeout(30);  // set timeout to 30 sec.
        sqLiteStatement.executeUpdate("drop table if exists cities");
        sqLiteStatement.executeUpdate("create table cities (" +
                "name string, " +
                "country string, " +
                "lat float, " +
                "lon float)");
        sqLiteStatement.executeUpdate("drop table if exists countries");
        sqLiteStatement.executeUpdate("create table countries (name string)");
    }

    public static void main (String[] args) throws Exception {

        initSqLite();

        Class.forName("org.gjt.mm.mysql.Driver");
        Connection c = DriverManager.getConnection("jdbc:mysql://localhost/astro", "root", "admin");
        PreparedStatement GET_CITY = c.prepareStatement("" +
                "SELECT id, names_name_code, population, latitude, longitude, countries_name FROM cities " +
                "WHERE floor(latitude/1000)=? and floor(longitude/1000)=?  AND countries_name NOT LIKE '%Antarctica%' " +
                "ORDER BY population DESC LIMIT 1");

        ArrayList<String> countries = new ArrayList<String>();

        for (int lat = -14; lat<14; lat++) {
            for (int lon = -9; lon<9; lon++) {

                GET_CITY.setInt(1, lat);
                GET_CITY.setInt(2, lon);
                ResultSet rs = GET_CITY.executeQuery();
                if (rs.next()) {
                    System.out.println(
                            String.format("LON=%d LAT=%d City is %s (%s) with population %d",
                                    rs.getInt(5), rs.getInt(4), rs.getString(2).trim(), rs.getString(6), rs.getInt(3)));
                    if (!countries.contains(rs.getString(6))) {
                        countries.add(rs.getString(6));
                        String country = String.format("insert into countries values ('%s')",rs.getString(6));
                        System.out.println(country);
                        sqLiteStatement.executeUpdate(country);
                    }

                    String city = String.format("insert into cities values ('?', '?', ?, ?)",
                            rs.getString(2), rs.getString(6), rs.getInt(4)/10, rs.getInt(5)/10);
                    sqLiteStatement.executeUpdate(city);

                }


            }
        }

        for (String country : countries) {
            System.out.println(country);
        }

    }

}
