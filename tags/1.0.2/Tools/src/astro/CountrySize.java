package astro;

import java.io.BufferedReader;
import java.io.FileReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

/**
 * Created with IntelliJ IDEA.
 * User: ddreval
 * Date: 01.04.13
 * Time: 12:46
 * To change this template use File | Settings | File Templates.
 */
public class CountrySize {

    public static void main(String[] args) throws Exception {

        Class.forName("org.gjt.mm.mysql.Driver");
        Connection c = DriverManager.getConnection("jdbc:mysql://localhost/astro", "root", "admin");
        PreparedStatement ps = c.prepareStatement("UPDATE countries SET border_length=?, area=? where names_name_code=?");

        BufferedReader br = new BufferedReader(new FileReader("ListAreaLen.txt"));
        while (br.ready()) {
            String line = br.readLine();
            String parts[] = line.split("\t");
            System.out.println(parts[1]);

            ps.setInt(1, (int)Float.parseFloat(parts[2]));
            ps.setInt(2, (int)Float.parseFloat(parts[3]));
            ps.setString(3, parts[1]);

            ps.execute();
        }



    }


}
