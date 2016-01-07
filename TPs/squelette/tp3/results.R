iss <- scan("iss_samples")
natif <- scan("native_samples")
iss <- iss * 10 ^ -9
natif <- natif * 10 ^ -9
difference <- iss - natif
pdf("difference.pdf")
plot(difference)
dev.off()
