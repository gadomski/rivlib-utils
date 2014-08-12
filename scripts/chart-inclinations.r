library(ggplot2)
library(reshape2)

filenames <- c("140123_202748_inclinations.txt",
               "140201_185848_inclinations.txt",
               "140226_163837_inclinations.txt")
FILENAME_INDEX <- 3

inclinations <- read.csv(paste0("~/Code/rivlib-development/data/Zuma/", filenames[FILENAME_INDEX]))
inclinations <- inclinations[inclinations$Time > 0,]
inclinations["Distance"] <- sqrt(inclinations["Roll"] ^ 2 + inclinations["Pitch"] ^ 2)
inclinations.melt <- melt(inclinations, id="Time", value.name = "Degrees")

p <- ggplot(inclinations.melt, aes(Time, Degrees)) +
    geom_point(alpha = 1/4) +
    facet_grid(variable ~ ., scales = "free") +
    ggtitle(filenames[FILENAME_INDEX])
p
