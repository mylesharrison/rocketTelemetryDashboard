import matplotlib.pyplot as plt
times = []
altitudes =[]
def update_graph(times, altitudes):
    plt.clf()
    plt.plot(times, altitudes)
    plt.xlabel("Time (ms)")
    plt.ylabel("Altitude (m)")
    plt.title("Real-time Altitude")
    plt.pause(0.01)
def graphPlot(time_ms, altitude):
    # Append time and altitude to lists for graphing
    times.append(float(time_ms))
    altitudes.append(float(altitude))
#update graph as new data comes in      
    MAX_POINTS = 50

    if len(times) > MAX_POINTS:
        times.pop(0)
        altitudes.pop(0)
    update_graph(times, altitudes)