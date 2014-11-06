package astro;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

/**
 * Created by:          $Author:: ddreval
 * Creation time:       $Date:: 2012-11-22 11:28
 * Last modified by:    $Author::                   $
 * Modification time:   $Date::                     $
 * File revision:       $Rev::                      $
 */
public class ConstellationNames {

    public static void main(String[] args) throws Exception {

        fill (1, "deu-DE.xml");
        fill (3, "ara-AE.xml");
        fill (4, "zho-CN.xml");
        fill (5, "eng-GB.xml");
        fill (6, "fin-FI.xml");
        fill (7, "fra-FR.xml");
        fill (8, "ita-IT.xml");
//        fill (8, "ita-IT.xml"); Japan?
        fill (11, "fas-IR.xml");
        fill (12, "rus-RU.xml");
        fill (13, "spa-US.xml");
        fill (14, "ces-CZ.xml");
        fill (15, "tur-TR.xml");

// 1 Deutsch
// 2 Latein
// 3 Arabisch
// 4 Chinesisch
// 5 Englisch
// 6 Finnisch
// 7 Französisch
// 8 Italienisch
// 9 Japanisch
// 10 Koreanisch
// 11 Persisch
// 12 Russisch
// 13 Spanisch
// 14 Tschechisch
// 15 Türkisch



    }

    public static void fill (int colNum, String fileName) throws Exception {

        BufferedReader br = new BufferedReader(new FileReader("__ConstTabbed.txt"));
        BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));



        bw.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
        bw.write("<string_table Bversion=\"2.0.3.v20111206\" Dversion=\"20100701\">\n");

        while (br.ready()) {
            String str = br.readLine();
            String[] names = str.split("\t");
            System.out.println(names[2]);
            bw.write("\t<text id=\""+names[0].toUpperCase()+"\">"+names[colNum]+"</text>\n");
        }

        bw.write("</string_table>");

        bw.flush();
        bw.close();
        br.close();


    }

}
