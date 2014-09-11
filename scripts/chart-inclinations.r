library(ggplot2)
library(reshape2)
library(plyr)
library(zoo)

filenames <- c(
               "Zuma/140117_160540_inclinations.txt",
               "Zuma/140117_163141_inclinations.txt",
               "Zuma/140123_202748_inclinations.txt",
               "Zuma/140201_185848_inclinations.txt",
               "Zuma/140226_163837_inclinations.txt",
               "EastWall/140123_180026_inclination.txt",
               "EastWall/140201_205741_inclination.txt")

getInclinations <- function(filename, referenceDistance=0)
{
    inclinations = read.csv(paste0("~/Code/rivlib-development/data/", filename))
    inclinations <- inclinations[inclinations$Time > 0,]
    means <- colMeans(inclinations[1:10,])
    inclinations["Roll"] <- inclinations["Roll"] - means["Roll"]
    inclinations["Pitch"] <- inclinations["Pitch"] - means["Pitch"]
    if (referenceDistance > 0)
    {
        inclinations[c("Roll", "Pitch")] = referenceDistance * tan(inclinations[c("Roll", "Pitch")] * pi / 180)
    }
    inclinations["Magnitude"] <- sqrt(inclinations["Roll"] ^ 2 + inclinations["Pitch"] ^ 2)
    return(inclinations)
}

getMassagedInclinations <- function(filename, mean_window=0, referenceDistance=0)
{
    inclinations = getInclinations(filename, referenceDistance)
    if (referenceDistance > 0)
    {
        return(melt(inclinations, id="Time", value.name="Error"))
    }
    else
    {
        rollpitch <- melt(inclinations, .(Roll, Pitch), id="Time", value.name="Degrees")
        if (mean_window > 0)
        {
            temp.roll <- zoo(inclinations$Roll, inclinations$Time)
            temp.pitch <- zoo(inclinations$Pitch, inclinations$Time)
            inclinations$Roll = rollmean(temp.roll, mean_window, fill = list(NA, NULL, NA))
            inclinations$Pitch = rollmean(temp.pitch, mean_window, fill = list(NA, NULL, NA))
            means <- melt(inclinations, .(Roll, Pitch), id="Time", value.name="Mean")
            rollpitch <- merge(rollpitch, means)
        }
        return(rollpitch)
    }
}

plotInclinations <- function(filename, mean_window = 0)
{
    inclinations.melt <- getMassagedInclinations(filename, mean_window)

    p <- ggplot(inclinations.melt, aes(Time, Degrees)) +
        geom_point(alpha = 1/4) +
        facet_grid(variable ~ .) +
        ggtitle(filename)

    if (mean_window > 0)
    {
        p <- p + geom_line(aes(Time, Mean), colour="red")
    }
    return(p)
}


plotErrors <- function(filename, referenceDistance)
{
    inclinations.melt <- getMassagedInclinations(filename, referenceDistance)

    p <- ggplot(inclinations.melt, aes(Time, Error)) +
        geom_point(alpha = 1/4) +
        facet_grid(variable ~ .) +
        ggtitle(filename) +
        ylab(paste0("Error at ", referenceDistance, "m, in meters"))
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
    return(p)
}

saveEachInclination <- function(referenceDistance=0, mean_window=0)
{
    extension = ".png"
    if (referenceDistance > 0)
    {
        suffix = paste0("_", referenceDistance, "m")
    }
    else
    {
        suffix = ""
    }

    for (filename in filenames)
    {
        imageFilename <- paste0("~/Desktop/InclinationImages/",
                                gsub(".txt", paste0(suffix, extension),
                                     gsub("/", "_", filename)))
        if (referenceDistance > 0)
        {
            p <- plotErrors(filename, referenceDistance)
        }
        else
        {
            p <- plotInclinations(filename, mean_window)
        }
        ggsave(p, filename = imageFilename)
    }
}
