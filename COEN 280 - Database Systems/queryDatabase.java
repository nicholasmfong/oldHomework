package coen.pkg280.hw.pkg3;
import java.sql.*;
import java.io.*;
import java.util.Arrays;

//import oracle.jdbc.driver.OracleDriver;
class queryDatabase{
    public static ResultSet main(String query){  
        try{  
            //Connect to DB
            Class.forName("oracle.jdbc.driver.OracleDriver");
            Connection dbConnection;
            dbConnection = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1522:ORCL","scott","tiger");         
            Statement stmt = dbConnection.createStatement();
            ResultSet result = stmt.executeQuery(query);
            //dbConnection.close();  
            return result;
        }catch(Exception e){
            System.out.println(e);
            return null;
        }  
    } 
}  