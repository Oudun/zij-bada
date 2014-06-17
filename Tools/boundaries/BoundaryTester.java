import java.io.*;
import java.util.*;

public class BoundaryTester {
	
	public static void main(String[] args) throws Exception {


		StringBuilder sb = new StringBuilder();
		sb.append("<html><body>");
		sb.append("<script type=\"text/javascript\">");


		File file = new File("and.txt");	
		BufferedReader br = new BufferedReader(new FileReader(file));


		sb.append("var poly=[ ");




		while (br.ready()) {

			String line = br.readLine();
			int x = (int)(10*Float.parseFloat(line.substring(5, 13)));
			int y = (int)(10*Float.parseFloat(line.substring(14, 25)));
			sb.append(x);
			sb.append(",");
			sb.append(y);
			sb.append(", ");

		}
		sb.deleteCharAt(sb.length()-2);


		System.out.println(sb.toString());

		sb.append("</script>");
		sb.append("<body><html>");


		FileWriter fw = new FileWriter("test.html");
		fw.write(sb.toString());
		fw.close();



	}

/*
var poly=[ 5,5, 100,50, 50,100, 10,90 ];
var canvas=document.getElementById("canvas")
var ctx = canvas.getContext('2d');
ctx.fillStyle = '#f00';

ctx.beginPath();
ctx.moveTo(poly[0], poly[1]);
for( item=2 ; item < poly.length-1 ; item+=2 ){ctx.lineTo( poly[item] , poly[item+1] )}

ctx.closePath();
ctx.fill();
*/

}