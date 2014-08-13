library(ggplot2)
library(reshape2)
library(plyr)

filenames <- c(
               "Zuma/140117_160540_inclinations.txt",
               "Zuma/140117_163141_inclinations.txt",
               "Zuma/140123_202748_inclinations.txt",
               "Zuma/140201_185848_inclinations.txt",
               "Zuma/140226_163837_inclinations.txt",
               "EastWall/140123_180026_inclination.txt",
               "EastWall/140201_205741_inclination.txt")

getInclinations <- function(filename)
{
    return(read.csv(paste0("~/Code/rivlib-development/data/", filename)))
}

massageInclinations <- function(inclinations)
{
    inclinations <- inclinations[inclinations$Time > 0,]
    means <- colMeans(inclinations[1:10,])
    inclinations["Roll"] <- inclinations["Roll"] - means["Roll"]
    inclinations["Pitch"] <- inclinations["Pitch"] - means["Pitch"]
    inclinations["Distance"] <- sqrt(inclinations["Roll"] ^ 2 + inclinations["Pitch"] ^ 2)
    return(melt(inclinations, id="Time", value.name = "Degrees"))
}

getMassagedInclinations <- function(filename)
{
    return(massageInclinations(getInclinations(filename)))
}

plotInclinations <- function(filename)
{
    inclinations.melt <- getMassagedInclinations(filename)

    p <- ggplot(inclinations.melt, aes(Time, Degrees)) +
        geom_point(alpha = 1/4) +
        facet_grid(variable ~ .) +
        ggtitle(filename)
    return(p)
}

plotAllInclinations <- function()
{
    allInclinations <- adply(data.frame(filename=I(filenames)),
                                1,
                                with,
                                cbind(getMassagedInclinations(filename), filename=filename))
    p <- ggplot(allInclinations, aes(Time, Degrees)) +
        geom_point(alpha = 1/4) +
        facet_grid(variable ~ filename) +
        ggtitle("All inclination charts")
    print(p)
    return(p)
}

saveEachInclination <- function()
{
    for (filename in filenames)
    {
        imageFilename <- paste0("~/Desktop/", gsub(".txt", ".png", gsub("/", "_", filename)))
        ggsave(plotInclinations(filename), filename = imageFilename)
    }
}
