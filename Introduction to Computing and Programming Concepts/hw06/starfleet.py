# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 6

import datetime

#==========================================
# Purpose: CrewMember is a class that takes the names, ids, ranks, and stats of starfleet Crew members and stores them as CrewMember objects that can be called and changed with various methods, setters, and getters
# Input Parameter(s): crew_id, last_name, first_name, rank, and stats are the initial input values that represent what you’d think
# Return Value(s): You could use getters to return the names, names, rank, id, and stats of a crewmember, or the methods(explained below) to return specifically altered values, lists, or tuples
#==========================================
class CrewMember:
    def __init__(self, crew_id, last_name=[], first_name=[], rank=[]):
        self.crew_id = crew_id
        self.last_name = last_name
        self.first_name = first_name
        self.rank = rank
        self.stats = ([], [], [])

    def set_last_name(self, string): ########### Setters ###########
        self.last_name = str(string)
    def set_first_name(self, string):
        self.first_name = str(string)
    def set_rank(self, string):
        self.rank = str(string)

    def get_crew_id(self): ########### Getters ###########
        return self.crew_id
    def get_last_name(self):
        return self.last_name
    def get_first_name(self):
        return self.first_name
    def get_rank(self):
        return self.rank
    def get_stats(self):
        return list(self.stats)

#==========================================
# Purpose: add_stats’s purpose is to add a value to the physical, job, or review stat based off the one the user picks
# Input Parameter(s): integer and string, where integer is the value the person wishes to add as a stat, and string, P, J, or R, represents where they want to put that stat
# Return Value(s): nothing gets returned, it modifies self.stats though
#==========================================
    def add_stats(self, integer, string): ########### Methods ###########
        if string == "P":
            self.stats[0].append(integer)
        if string == "J":
            self.stats[1].append(integer)
        if string == "R":
            self.stats[2].append(integer)

#==========================================
# Purpose: average_stats will return a tuple of averages for a crewmember object’s stats
# Input Parameter(s): nothing, it uses the existing stats
# Return Value(s): a tuple with 3 averaged elements is returned, 0th is physical training scores, 1st is job test scores, 2nd is review ratings
#==========================================
    def average_stats(self):
        if len(self.stats[0]) != 0:
            physical_training_avg = (sum(self.stats[0])) / (len(self.stats[0]))
        else:
            physical_training_avg = 0
        if len(self.stats[1]) != 0:
            job_test_scores_avg = (sum(self.stats[1])) / (len(self.stats[1]))
        else:
            job_test_scores_avg = 0
        if len(self.stats[2]) != 0:
            review_ratings_avg = (sum(self.stats[2])) / (len(self.stats[2]))
        else:
            review_ratings_avg = 0
        avg_stats_tuple = (round(physical_training_avg), round(job_test_scores_avg), round(review_ratings_avg))
        return avg_stats_tuple

#==========================================
# Purpose: __str__ function is overloaded here so that when the CrewMember object is asked to be printed, it prints out everything in a nice format
# Input Parameter(s): None
# Return Value(s): returns a string using format with a section on every new line, ID, Stats, and Averages
#==========================================
    def __str__(self): ########### Overloading ###########
        if len(self.stats[0]) != 0:
            physical_training_avg = (sum(self.stats[0])) / (len(self.stats[0]))
        else:
            physical_training_avg = 0
        if len(self.stats[1]) != 0:
            job_test_scores_avg = (sum(self.stats[1])) / (len(self.stats[1]))
        else:
            job_test_scores_avg = 0
        if len(self.stats[2]) != 0:
            review_ratings_avg = (sum(self.stats[2])) / (len(self.stats[2]))
        else:
            review_ratings_avg = 0
        avg_stats_tuple = (round(physical_training_avg), round(job_test_scores_avg), round(review_ratings_avg))
        return "ID: {}\nStats: {}\nAverages: {}".format(self.crew_id, self.stats, avg_stats_tuple)

########### Testing the Code ###########
#member_list = [CrewMember(13345, "Scott", "Michael", "Regional Commander"), CrewMember(14523, "Blunt", "Emily", "Lieutenant"), CrewMember(17343, "Shrute", "Dwight", "Assistant to the Regional Commander")]

#member_list[2].add_stats(2, 'P') #testing add_stats
#member_list[2].add_stats(6, 'P')
#member_list[1].add_stats(6, 'P')
#member_list[0].add_stats(3, 'J')
#member_list[0].add_stats(5, 'J')
#member_list[0].add_stats(7, 'J')
#member_list[1].add_stats(2, 'R')

#for i in member_list: #testing the overloaded __str__
#    print(i) #idk what it means by "using the print() function with the object name as its input." 

#member_list[1].set_last_name("Beasly") #testing set_last_name
#member_list[1].set_first_name("Pam") #testing set_first_name
#member_list[1].set_rank("Previous Secretary") #testing set_rank

#print(member_list[0].get_crew_id(), member_list[1].get_crew_id(), member_list[2].get_crew_id()) #testing get_crew
#print(member_list[0].get_last_name(), member_list[1].get_last_name(), member_list[2].get_last_name()) #testing get_last_name
#print(member_list[0].get_first_name(), member_list[1].get_first_name(), member_list[2].get_first_name()) #testing get_first_name
#print(member_list[0].get_rank(), member_list[1].get_rank(), member_list[2].get_rank()) #testing get_rank
#print(member_list[0].get_stats(), member_list[1].get_stats(), member_list[2].get_stats()) #testing get_stats

#print(member_list[0].average_stats()) #testing average_stats

#==========================================
# Purpose: the StarshipCrew is a class which inherits from the class CrewMember and is meant to be an object used to store information about a starship (its manufacture date, ship class, start of mission, and its crew members) to use with various getters, setters, and methods
# Input Parameter(s): input parameters include starship_name (string that is the name of starship), manufactured_year (integer that is the manufactured year), ship_class(string thats the ships class), start_date_of_current_mission (datetime object that is the first day the ship started its current mission), and crew(a list of CrewMember Objects).
# Return Value(s): you could use the getter to return a list of the crew member objects, or methods to return the length of crew, or amount of people with a certain rank
#==========================================
class StarshipCrew(CrewMember):
    def __init__(self, starship_name, manufactured_year, ship_class, start_date_of_current_mission, crew=[]):
        self.starship_name = starship_name
        self.manufactured_year = manufactured_year
        self.ship_class = ship_class
        self.start_date_of_current_mission = start_date_of_current_mission
        self.crew = crew

    def get_crew(self):
        return self.crew

#==========================================
# Purpose: print_crew prints all the CrewMember objects of the Starship Crew
# Input Parameter(s): none
# Return Value(s): none
#==========================================
    def print_crew(self):
        for i in self.crew:
            print(i)

#==========================================
# Purpose: Count returns the length of the crew list, how many crew members are on the startfleet
# Input Parameter(s): None
# Return Value(s): returns the length of self.crew, a list of CrewMember objects
#==========================================
    def count(self):
        return len(self.crew)

#==========================================
# Purpose: count_crew_rank takes a ranking and looks to see how many people on the starfleet have that particular ranking
# Input Parameter(s): ranking, which will be a string that is a persons title
# Return Value(s): x get returned, x is a counter thats added to everytime an iteration has a desired ranking
#==========================================
    def count_crew_rank(self, ranking):
        x = 0
        for i in self.crew:
            if i.get_rank() == ranking:
                x += 1
        return x

#==========================================
# Purpose: add_crew adds a new CrewMember object (person) to the crew list
# Input Parameter(s): New_member, which has to be a CrewMember object
# Return Value(s): None
#==========================================
    def add_crew(self, New_Member):
        self.crew.append(New_Member)

#==========================================
# Purpose: This __str__ function overloads the printing function for StarshipCrew and returns a nicely formated list of everything, but also takes the average of all the Crew Member's stats and puts that in a tuple thats also averaged
# Input Parameter(s): None
# Return Value(s): returns the starship_name (string), manufactured_year(integer), ship_class(string), start_date_of_current mission(datetime object), and true_average (tuple)
#==========================================
    def __str__(self):
        physical_training_avg = 0
        job_test_scores_avg = 0
        review_ratings_avg = 0
        for i in self.crew:
            if len(i.stats[0]) != 0:
                physical_training_avg += (sum(i.stats[0])) / (len(i.stats[0]))
            if len(i.stats[1]) != 0:
                job_test_scores_avg += (sum(i.stats[1])) / (len(i.stats[1]))
            if len(i.stats[2]) != 0:
                review_ratings_avg += (sum(i.stats[2])) / (len(i.stats[2]))

        true_average = (round(physical_training_avg / len(self.crew)), round(job_test_scores_avg / len(self.crew)), round(review_ratings_avg / len(self.crew)))
        return "{}, {}, {}, {}, {}".format(self.starship_name, self.manufactured_year, self.ship_class, self.start_date_of_current_mission, true_average)

########### Testing the Code ###########
#print("\n\n----------\n\n") #to make the info easier to see when testing

#x = StarshipCrew('Enterprise', 2020, 'Freighter', datetime.date(2002, 9, 7))
#print(x.get_crew())

#person1 = CrewMember(1, "Tong", "Minh", "Lieutenant")
#person2 = CrewMember(14523, "Blunt", "Emily", "Lieutenant")
#person3 = CrewMember(17343, "Shrute", "Dwight", "Assistant to the Regional Commander")
#x.add_crew(person1)
#x.add_crew(person2)
#x.add_crew(person3)

#person1.add_stats(2, 'P')
#person1.add_stats(3, 'P')
#person1.add_stats(4, 'P')
#person1.add_stats(9, 'J')
#person1.add_stats(8, 'J')
#person2.add_stats(8, 'J')
#person2.add_stats(9, 'J')

#x.print_crew()
#print(x.count())
#print(x.count_crew_rank("Lieutenant"))

#print(x)