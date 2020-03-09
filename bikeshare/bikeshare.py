import time
import pandas as pd
import numpy as np

CITY_DATA = { 'chicago': 'chicago.csv',
              'new york city': 'new_york_city.csv',
              'washington': 'washington.csv' }

def get_filters():
    """
    Asks user to specify a city, month, and day to analyze.

    Returns:
        (str) city - name of the city to analyze
        (str) month - name of the month to filter by, or "all" to apply no month filter
        (str) day - name of the day of week to filter by, or "all" to apply no day filter
    """
    print('Hello! Let\'s explore some US bikeshare data!')
    
    # get user input for city (chicago, new york city, washington). HINT: Use a while loop to handle invalid inputs
    while True:
        city = input('\nWhich city you would like to explore? chicago,new york city or washington?\n')
        if city not in ('chicago','new york city','washington'):
            print("Sorry, I didn't get that\n")
            continue
        else:
            break 
            
            
    #get user input for month (all, january, february, ... , june)    
    while True:
        month = input("\nWhich month you would like to explore? January,February,March,April,May,June or type 'all' if you do not have any preference?\n")
        if month not in ('January','February','March','April','May','June','all'):
            print("Sorry, I didn't get that\n")
            continue
        else:
            break 


    #get user input for day of week (all, monday, tuesday, ... sunday)
    while True:
        day = input("\nWhich week you would like to explore? Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday or type 'all' if you do not have any preference?\n")
        if day not in ('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday','all'):
            print("Sorry, I didn't get that\n")
            continue
        else:
            break


    print('-'*40)
    return city, month, day


def load_data(city, month, day):
    """
    Loads data for the specified city and filters by month and day if applicable.

    Args:
        (str) city - name of the city to analyze
        (str) month - name of the month to filter by, or "all" to apply no month filter
        (str) day - name of the day of week to filter by, or "all" to apply no day filter
    Returns:
        df - Pandas DataFrame containing city data filtered by month and day
    """
    
    #read the data from the file of the specified city
    df=pd.read_csv(CITY_DATA[city])
    
    #convert start time column to date time format
    df['Start Time'] = pd.to_datetime(df['Start Time'])
    
    #extract month and day from start time to create new columns
    df['month'] = df['Start Time'].dt.month
    df['day_of_week'] = df['Start Time'].dt.weekday_name
    
    #filter by month if applicable
    if month!='all':
        months=['January','February','March','April','May','June']
        month = months.index(month)+1
        df = df[df['month']==month]
     
    #filter by day if applicable
    if day!='all':
        df = df[df['day_of_week']==day.title()]   

    return df


def time_stats(df):
    """Displays statistics on the most frequent times of travel."""

    print('\nCalculating The Most Frequent Times of Travel...\n')
    start_time = time.time()

    #display the most common month
    popular_month = df['month'].mode()[0]
    print("The most common Month: ",popular_month)


    #display the most common day of week
    popular_day = df['day_of_week'].mode()[0]
    print("The most common Day: ",popular_day)


    #display the most common start hour
    df['Hour']=df['Start Time'].dt.hour
    popular_hour=df['Hour'].mode()[0]
    print("The most common Hour: ",popular_hour)


    print("\nThis took %s seconds." % (time.time() - start_time))
    print('-'*40)


def station_stats(df):
    """Displays statistics on the most popular stations and trip."""

    print('\nCalculating The Most Popular Stations and Trip...\n')
    start_time = time.time()

    #display most commonly used start station
    start_station = df['Start Station'].value_counts().idxmax()
    print("The most commonly used start station: ",start_station)


    #display most commonly used end station
    end_station = df['End Station'].value_counts().idxmax()
    print("The most commonly used end station: ",end_station)


    #display most frequent combination of start station and end station trip
    combination_trip = df['Start Station'].astype(str) + " to " + df['End Station'].astype(str)
    most_frequent_trip = combination_trip.value_counts().idxmax()
    print('\nMost popular trip is from {}\n'.format(most_frequent_trip))
    


    print("\nThis took %s seconds." % (time.time() - start_time))
    print('-'*40)


def trip_duration_stats(df):
    """Displays statistics on the total and average trip duration."""

    print('\nCalculating Trip Duration...\n')
    start_time = time.time()

    #display total travel time
    total_travel_time = sum(df['Trip Duration'])
    print("Total travel time: ", total_travel_time/3600, "hours")


    #display mean travel time
    mean_travel_time=df['Trip Duration'].mean()
    print("Mean travel time: ",mean_travel_time/60, "minutes")


    print("\nThis took %s seconds." % (time.time() - start_time))
    print('-'*40)


def user_stats(df):
    """Displays statistics on bikeshare users."""

    print('\nCalculating User Stats...\n')
    start_time = time.time()

    #Display counts of user types
    user_types = df['User Type'].value_counts()
    print("User types\n" ,user_types)
                    


    #Display counts of gender
    try:
      gender_types = df['Gender'].value_counts()
      print('\nGender Types:\n', gender_types)
    except KeyError:
      print("\nGender Types:\nNo data available for this month.")


    #Display earliest, most recent, and most common year of birth
    try:
      earliest_year = df['Birth Year'].min()
      print('\nEarliest Year:', earliest_year)
    except KeyError:
      print("\nEarliest Year:\nNo data available for this month.")

    try:
      most_recent_year = df['Birth Year'].max()
      print('\nMost Recent Year:', most_recent_year)
    except KeyError:
      print("\nMost Recent Year:\nNo data available for this month.")

    try:
      most_common_year = df['Birth Year'].value_counts().idxmax()
      print('\nMost Common Year:', most_common_year)
    except KeyError:
      print("\nMost Common Year:\nNo data available for this month.")


    print("\nThis took %s seconds." % (time.time() - start_time))
    print('-'*40)


def main():
    while True:
        city, month, day = get_filters()
        df = load_data(city, month, day)

        time_stats(df)
        station_stats(df)
        trip_duration_stats(df)
        user_stats(df)

        restart = input('\nWould you like to restart? Enter yes or no.\n')
        if restart.lower() != 'yes':
            break


if __name__ == "__main__":
	main()
