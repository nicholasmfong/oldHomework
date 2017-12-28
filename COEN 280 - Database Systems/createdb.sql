--Nicholas Fong COEN 280 HW 3
CREATE TABLE movieActors(
    movieID    NUMBER,
    actorID    VARCHAR(50),
    actorName  VARCHAR(50),
    ranking    NUMBER,
    PRIMARY KEY (movieID, actorID)
);

CREATE TABLE movieCountries(
    movieID    NUMBER,
    country    VARCHAR(50)
);

CREATE TABLE movieDirectors(
    movieID      NUMBER,
    directorID   VARCHAR(50),
    directorName VARCHAR(50),
    PRIMARY KEY (movieID, directorID)
);

CREATE TABLE movieGenres(
    movieID    NUMBER,
    genre      VARCHAR(50)
);

CREATE TABLE movieLocations(
    movieID    NUMBER,
    country    VARCHAR(50),
    state      VARCHAR(50),
    city       VARCHAR(75),
    street     VARCHAR(150)
);
CREATE TABLE movieTags(
    movieID    NUMBER,
    tagID      NUMBER,
    tagWeight  NUMBER
);

CREATE TABLE movies(
    movieID         NUMBER PRIMARY KEY,
    title           VARCHAR(125),
    imdbID          NUMBER,
    spanishTitle    VARCHAR(100),
    imdbPictureURL  VARCHAR(150),
    year            NUMBER,
    rtID            VARCHAR(100),
    rtACRating      NUMBER,
    rtACNumReviews  NUMBER,
    rtACNumFresh    NUMBER,
    rtACNumRotten   NUMBER,
    rtACScore       NUMBER,
    rtTCRating      NUMBER,
    rtTCNumReviews  NUMBER,
    rtTCNumFresh    NUMBER,
    rtTCNumRotten   NUMBER,
    rtTCScore       NUMBER,
    rtAudRating     NUMBER,
    rtAudNumRatings NUMBER,
    rtAudScore      NUMBER,
    rtPictureURL    VARCHAR(150)
);

CREATE TABLE tags(
    tagID    NUMBER PRIMARY KEY,
    text     VARCHAR(100)
);

CREATE TABLE userRatedMovies(
    userID    NUMBER,
    movieID   NUMBER,
    rating    NUMBER,
    day       NUMBER,
    month     NUMBER,
    year      NUMBER,
    hour      NUMBER,
    minute    NUMBER,
    second    NUMBER,
    PRIMARY KEY (userID, movieID)
);

CREATE TABLE userRatedMoviesTimestamps(
    userID    NUMBER,
    movieID   NUMBER,
    rating    NUMBER,
    timestamp NUMBER,
    PRIMARY KEY (userID, movieID)
);

CREATE TABLE userTaggedMovies(
    userID    NUMBER,
    movieID   NUMBER,
    tagID     NUMBER,
    day       NUMBER,
    month     NUMBER,
    year      NUMBER,
    hour      NUMBER,
    minute    NUMBER,
    second    NUMBER,
    PRIMARY KEY (userID, movieID, tagID)
);

CREATE TABLE userTaggedMoviesTimestamps(
    userID    NUMBER,
    movieID   NUMBER,
    tagID     NUMBER,
    timestamp NUMBER,
    PRIMARY KEY (userID, movieID, tagID)
);

CREATE INDEX genreIndex
ON movieGenres (genre)
COMPUTE STATISTICS;

CREATE INDEX movieTagIndex
ON movieTags (tagWeight)
COMPUTE STATISTICS;

CREATE INDEX movieYearIndex
ON movies (year)
COMPUTE STATISTICS;

CREATE INDEX countryIndex
ON movieCountries (country)
COMPUTE STATISTICS;

CREATE INDEX actorIndex
ON movieActors (actorName)
COMPUTE STATISTICS;
