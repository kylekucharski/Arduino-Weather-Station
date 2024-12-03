import pandas as pd
import matplotlib.pyplot as plt

#Load the CSV file
weather_data = pd.read_csv('weather_station_data.csv')

#Clean and process the data
current_year = pd.Timestamp.now().year
weather_data['Cleaned Date'] = weather_data['Date'].str.replace(r'^\w+, ', '', regex=True) + f" {current_year}"
weather_data['Datetime'] = pd.to_datetime(weather_data['Cleaned Date'] + ' ' + weather_data['Time'], errors='coerce')

#Drop unnecessary columns
weather_data_cleaned = weather_data.drop(columns=['Date', 'Time', 'Cleaned Date'])
weather_data_cleaned = weather_data_cleaned[['Datetime', 'Temperature (F)', 'Humidity (%)']]

#Plot Temperature over time
plt.figure(figsize=(10, 6))
plt.plot(weather_data_cleaned['Datetime'], weather_data_cleaned['Temperature (F)'], label='Temperature (F)')
plt.title('Temperature Over Time')
plt.xlabel('Datetime')
plt.ylabel('Temperature (F)')
plt.legend()
plt.grid()
plt.show()

#Plot Humidity over time
plt.figure(figsize=(10, 6))
plt.plot(weather_data_cleaned['Datetime'], weather_data_cleaned['Humidity (%)'], label='Humidity (%)', color='orange')
plt.title('Humidity Over Time')
plt.xlabel('Datetime')
plt.ylabel('Humidity (%)')
plt.legend()
plt.grid()
plt.show()

#Generate summary statistics
summary_statistics = weather_data_cleaned.describe()
print("Summary Statistics:")
print(summary_statistics)
