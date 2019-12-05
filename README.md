# Autocorrelation-Ramp-1
Code in C to calculate the beat frequency and range of 2 ADC signals (simultaneously) using 15 ramps.
	-
			The objectve of this program is to process 2 analog signals (I & Q) at the same time.
			The signals are sended by a FMCW 24GHz radar system connected to a ramp generator circuit and a 2 phase Amplifier.
			To obtain the range of a target from the radar, the beat frequency of the received signal is needed.
			The beat frequency can be estimated using: 
			sumatory from 0 to N-1 of the autocorrelation angle/(2pi(sampling period)(samples of ramp))
			The autocorrelation alge = angle(s(n+1)s*(n)) can be obtained from:
			angle 1 = atan(Q[n]/I[n])
			angle 2 = atan(Q[n+1]/I[n+1]
				autocorrelation angle = angle 1 - angle 2
			Once the beat frequency is obtained, the range per ramp is:
				Range = ((light velocity)(beat frequency)(sampling period))/((2*Bandwidht))
		-author: Karina Tañón-De Jesús Fall 2019
    Feel free to contribute in any way you like
