package xml_to_json;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import org.json.JSONException; // you may have to import the jar file from http://www.java2s.com/Code/JarDownload/java/java-json.jar.zip
import org.json.JSONObject;
import org.json.XML;

/**
 *
 * @author Nicholas COEN 280 HW 4
 */
public class Xml_to_JSON {

    public static int PRETTY_PRINT_INDENT_FACTOR = 4;
    
    public static void main(String[] args) throws FileNotFoundException {
        try {
            //you may have to rename the file
            String xml = new Scanner(new File("C:\\Nicholas\\CSCI\\COEN280\\students.xml")).useDelimiter("\\Z").next();
            JSONObject xmlJSONObj = XML.toJSONObject(xml);
            String jsonPrettyPrintString = xmlJSONObj.toString(PRETTY_PRINT_INDENT_FACTOR);
            System.out.println(jsonPrettyPrintString);
        } catch (JSONException je) {
            System.out.println(je.toString());
        }
    }
    
}
