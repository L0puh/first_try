from collections import deque

def BFS():
    seller = "Clara"

    graph = {}
    graph["you"] = ["Alice", "Tom"]
    graph["Alice"] = ["Magie", "you"]
    graph["Tom"] = ["Alice", "Daniel", "Clara"]
    graph["Magie"] = ["Tom", "Alice"]
    graph["Daniel"] = []
    graph["Clara"] = []

    search_engine = deque()
    search_engine += graph["you"]
    searched_people = []

    while search_engine:
        person = search_engine.popleft()
        print("search for ", person, "...")
        if person not in searched_people:
            if person == seller:
                print (person + " is a seller")
                return True
            print("add ", person,"'s friends to a queue")
            search_engine += graph[person]
            searched_people.append(person)
        else:
            print(person, "was searched already")

    return False

BFS()


