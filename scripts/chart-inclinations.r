library(ggplot2)
library(reshape2)

filenames <- c("Zuma/140123_202748_inclinations.txt",
               "Zuma/140201_185848_inclinations.txt",
               "Zuma/140226_163837_inclinations.txt",
               "EastWall/140123_180026_inclination.txt",
               "EastWall/140201_205741_inclination.txt")

plotInclinations <- function(idx)
{
    inclinations <- read.csv(paste0("~/Code/rivlib-development/data/", filenames[idx]))
    inclinations <- inclinations[inclinations$Time > 0,]
    inclinations["Distance"] <- sqrt(inclinations["Roll"] ^ 2 + inclinations["Pitch"] ^ 2)
    inclinations.melt <- melt(inclinations, id="Time", value.name = "Degrees")

    p <- ggplot(inclinations.melt, aes(Time, Degrees)) +
        geom_point(alpha = 1/4) +
        facet_grid(variable ~ ., scales = "free") +
        ggtitle(filenames[idx])
    return(p)
}
