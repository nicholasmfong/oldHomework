package coen.pkg280.hw.pkg3;
import java.sql.*;
import java.io.*;
import java.util.Arrays;

//import oracle.jdbc.driver.OracleDriver;
class OracleCon{
    //Checks if a string can be converted into a number for inserting into the database
    public static boolean isParsable(String input){
        boolean parsable = true;
        try{
            Integer.parseInt(input);
        }catch(NumberFormatException e){
            try{
                Float.parseFloat(input);
            }catch(NumberFormatException ex){
                parsable = false;
            }
        }
        return parsable;
    }
    
    public static void main(String args[]){  
        try{  
            //Connect to DB
            Class.forName("oracle.jdbc.driver.OracleDriver");
            Connection dbConnection;
            dbConnection = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1522:ORCL","scott","tiger");         
            //declare variables
            String insertSQL;
            BufferedReader TSVFile;
            PreparedStatement preparedStatement;
            String dataRow;
            String[] dataArray;
            try{    //Insert data into movieActors table
                insertSQL = "INSERT INTO movieActors"
				+ "(movieID, actorID, actorName, ranking) VALUES"
				+ "(?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movie_actors.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 4);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.setString(3, dataArray[2]);
                    preparedStatement.setInt(4, Integer.parseInt(dataArray[3]));
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Actors data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into movieCountries table
                insertSQL = "INSERT INTO movieCountries"
				+ "(movieID, country) VALUES"
				+ "(?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movie_countries.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 2);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Countries data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into movieDirectors table
                insertSQL = "INSERT INTO movieDirectors"
				+ "(movieID, directorID, directorName) VALUES"
				+ "(?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movie_directors.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 3);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.setString(3, dataArray[2]);
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Directors data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into movieGenres table
                insertSQL = "INSERT INTO movieGenres"
				+ "(movieID, genre) VALUES"
				+ "(?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movie_genres.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 2);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Genres data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into movieLocations table
                insertSQL = "INSERT INTO movieLocations"
				+ "(movieID, country, state, city, street) VALUES"
				+ "(?,?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movie_locations.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 5);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.setString(3, dataArray[2]);
                    preparedStatement.setString(4, dataArray[3]);
                    preparedStatement.setString(5, dataArray[4]);
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Locations data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into movieTags table
                insertSQL = "INSERT INTO movieTags"
				+ "(movieID, tagID, tagWeight) VALUES"
				+ "(?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movie_tags.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 3);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setInt(2, Integer.parseInt(dataArray[1]));
                    preparedStatement.setInt(3, Integer.parseInt(dataArray[2]));
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Tags data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into movies table
                insertSQL = "INSERT INTO movies"
				+ "(movieID, title, imdbID, spanishTitle, imdbPictureURL, year, rtID, rtACRating, rtACNumReviews, rtACNumFresh, rtACNumRotten, rtACScore, rtTCRating, rtTCNumReviews, rtTCNumFresh, rtTCNumRotten, rtTCScore, rtAudRating, rtAudNumRatings, rtAudScore, rtPictureURL) VALUES"
				+ "(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\movies.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 21);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.setInt(3, Integer.parseInt(dataArray[2]));
                    preparedStatement.setString(4, dataArray[3]);
                    preparedStatement.setString(5, dataArray[4]);
                    preparedStatement.setInt(6, Integer.parseInt(dataArray[5]));
                    preparedStatement.setString(7, dataArray[6]);
                    if(isParsable(dataArray[7])){   //Catch missing \n data
                        preparedStatement.setFloat(8, Float.parseFloat(dataArray[7]));
                    } else{
                        preparedStatement.setNull(8, java.sql.Types.FLOAT);
                    }
                    if(isParsable(dataArray[8])){
                        preparedStatement.setInt(9, Integer.parseInt(dataArray[8]));
                    } else{
                        preparedStatement.setNull(9, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[9])){
                        preparedStatement.setInt(10, Integer.parseInt(dataArray[9]));
                    } else{
                        preparedStatement.setNull(10, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[10])){
                        preparedStatement.setInt(11, Integer.parseInt(dataArray[10]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[11])){
                        preparedStatement.setInt(12, Integer.parseInt(dataArray[11]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[12])){
                        preparedStatement.setFloat(13, Float.parseFloat(dataArray[12]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.FLOAT);
                    }
                    if(isParsable(dataArray[13])){
                        preparedStatement.setInt(14, Integer.parseInt(dataArray[13]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[14])){
                        preparedStatement.setInt(15, Integer.parseInt(dataArray[14]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[15])){
                        preparedStatement.setInt(16, Integer.parseInt(dataArray[15]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[16])){
                        preparedStatement.setInt(17, Integer.parseInt(dataArray[16]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[17])){
                        preparedStatement.setFloat(18, Float.parseFloat(dataArray[17]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.FLOAT);
                    }
                    if(isParsable(dataArray[18])){
                        preparedStatement.setInt(19, Integer.parseInt(dataArray[18]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    if(isParsable(dataArray[19])){
                        preparedStatement.setInt(20, Integer.parseInt(dataArray[19]));
                    } else{
                        preparedStatement.setNull(11, java.sql.Types.INTEGER);
                    }
                    preparedStatement.setString(21, dataArray[20]);
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
             try{    //Insert data into tags table
                insertSQL = "INSERT INTO tags"
				+ "(tagID, text) VALUES"
				+ "(?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\tags.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 2);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setString(2, dataArray[1]);
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Tags data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into userRatedMovies table
                insertSQL = "INSERT INTO userRatedMovies"
				+ "(userID, movieID, rating, day, month, year, hour, minute, second) VALUES"
				+ "(?,?,?,?,?,?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\user_ratedmovies.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 9);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setInt(2, Integer.parseInt(dataArray[1]));
                    preparedStatement.setFloat(3, Float.parseFloat(dataArray[2]));
                    preparedStatement.setInt(4, Integer.parseInt(dataArray[3]));
                    preparedStatement.setInt(5, Integer.parseInt(dataArray[4]));
                    preparedStatement.setInt(6, Integer.parseInt(dataArray[5]));
                    preparedStatement.setInt(7, Integer.parseInt(dataArray[6]));
                    preparedStatement.setInt(8, Integer.parseInt(dataArray[7]));
                    preparedStatement.setInt(9, Integer.parseInt(dataArray[8]));
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Ratings data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into userRatedMoviesTimestamps table
                insertSQL = "INSERT INTO userRatedMoviesTimestamps"
				+ "(userID, movieID, rating, timestamp) VALUES"
				+ "(?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\user_ratedmovies-timestamps.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 4);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setInt(2, Integer.parseInt(dataArray[1]));
                    preparedStatement.setFloat(3, Float.parseFloat(dataArray[2]));
                    preparedStatement.setLong(4, Long.parseLong(dataArray[3]));
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("Movie Rating Timestamps data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into userTaggedMovies table
                insertSQL = "INSERT INTO userTaggedMovies"
				+ "(userID, movieID, tagID, day, month, year, hour, minute, second) VALUES"
				+ "(?,?,?,?,?,?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\user_taggedmovies.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 9);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setInt(2, Integer.parseInt(dataArray[1]));
                    preparedStatement.setInt(3, Integer.parseInt(dataArray[2]));
                    preparedStatement.setInt(4, Integer.parseInt(dataArray[3]));
                    preparedStatement.setInt(5, Integer.parseInt(dataArray[4]));
                    preparedStatement.setInt(6, Integer.parseInt(dataArray[5]));
                    preparedStatement.setInt(7, Integer.parseInt(dataArray[6]));
                    preparedStatement.setInt(8, Integer.parseInt(dataArray[7]));
                    preparedStatement.setInt(9, Integer.parseInt(dataArray[8]));
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("User Movie Tags data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            try{    //Insert data into userRatedMoviesTimestamps table
                insertSQL = "INSERT INTO userTaggedMoviesTimestamps"
				+ "(userID, movieID, tagID, timestamp) VALUES"
				+ "(?,?,?,?)";
                preparedStatement = dbConnection.prepareStatement(insertSQL);
                //Get the data
                TSVFile = new BufferedReader(new FileReader("C:\\Nicholas\\CSCI\\COEN280\\hw3\\coen280hw3data\\user_taggedmovies-timestamps.dat"));
                dataRow = TSVFile.readLine();
                dataRow = TSVFile.readLine();   //Repeat to skip the first header line
                while (dataRow != null){
                    dataArray = dataRow.split("\t");
                    dataArray = Arrays.copyOf(dataArray, 4);    //handle missing data
                    preparedStatement.setInt(1, Integer.parseInt(dataArray[0]));
                    preparedStatement.setInt(2, Integer.parseInt(dataArray[1]));
                    preparedStatement.setInt(3, Integer.parseInt(dataArray[2]));
                    preparedStatement.setLong(4, Long.parseLong(dataArray[3]));
                    preparedStatement.executeUpdate();
                    dataRow = TSVFile.readLine(); // Read next line of data.
                }
                System.out.println("User Movie Tag Timestamps data inserted");
            }catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            
            dbConnection.close();  
        }catch(Exception e){
            System.out.println(e);
        }  
    }  
}  