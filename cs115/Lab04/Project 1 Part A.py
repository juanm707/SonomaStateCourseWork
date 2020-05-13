'''
Doc string
'''
def main():

    print("*** Welcome to Olympic Medal Tally System ***")

    country = input("Enter country name: ")
    numSports = int(input("How many sports did *** " + str(country) + " *** participate in? "))

    print()
    # Counter
    totalmedals = 0
    yesMedal = 0
    noMedal = 0

    for i in range(numSports):
        sport = input("Enter name of ** Sport " + str(i + 1) + " ** : ")
        gold = int(input("\tEnter number of GOLD medals won in ** " + str(sport) + " ** : "))
        silver = int(input("\tEnter number of SILVER medals won in ** " + str(sport) + " ** : "))
        bronze = int(input("\tEnter number of BRONZE medals won in ** " + str(sport) + " ** : "))
        print()
        medals = gold + silver + bronze

        if medals > 0:
            yesMedal = yesMedal + 1

        else:
            noMedal = noMedal + 1

        weightedscore = round((0.6 * gold + 0.3 * silver + 0.1 * bronze), 3)
        totalmedals += medals
        print("\tTotal number of medals =", medals, "with a weighted score of", weightedscore)
        print()

    print("***** OVERALL STATISTICS *****")
    print("Number of sports that got a medal =", yesMedal)
    print("Number of sports that did not get a medal =", noMedal)
    avg = round((totalmedals / numSports), 3)
    print("Total Medals =", totalmedals, "with average of", avg, "medals per sport")


main()