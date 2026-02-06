#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <ranges>

// earliest arriving customer will get room 1, next earliest will go in room 2 if room 1 unoccupied
// and room 2 otherwise

// following, we can get the minimum number of rooms by assigning customers in order of arrival time, and 
// always assigning a customer to the room with earliest departure time if free, or new room if not free

// as soon as we fill a room we know when that room will be free, can maintain a list of rooms sorted by departure time
// and list of customers sorted by arrival time, iterate through each guest, assign to earliest available room or add new room

typedef std::tuple<int, int, int> guest_t; // (arrival, departure, order in input)
typedef std::pair<int, int> room_t; // (day room becomes available, room number)

int main()
{
    int n;
    std::cin >> n;

    std::vector<guest_t> guests;
    guests.reserve(n);

    // read guests
    for (int order_in_input : std::ranges::views::iota(0, n))
    {
        int arrival {}; int departure {};
        std::cin >> arrival >> departure;
        guests.push_back({ arrival, departure, order_in_input });
    }

    std::sort(guests.begin(), guests.end());

    // assign each guest to room with earliest departure < arrival time using min heap, or add new room if none available
    std::vector<int> assigned_rooms(n);
    std::vector<room_t> room_heap;
    room_heap.reserve(n); // worst case for heap size is n
    room_heap.push_back({ 0, 1 }); // room 1 is available from day 0

    for (auto [arrival, departure, order_in_input] : guests)
    {
        int room_assigned {};
        auto [earliest_free_day, earliest_free_room_num] = room_heap.front();

        // we need a new room if guest arrives earlier than room with earliest free date is free
        if (arrival <= earliest_free_day)
        {
            int new_room_num = room_heap.size() + 1;
            room_heap.push_back({ departure, new_room_num });
            room_assigned = new_room_num;
            std::push_heap(room_heap.begin(), room_heap.end(), std::greater<room_t>());
        }

        // otherwise assign guest to room that was free the earliest 
        else 
        {
            std::pop_heap(room_heap.begin(), room_heap.end(), std::greater<room_t>());
            auto [_, assigned_room_num] = room_heap.back(); 
            room_heap.back() = { departure, assigned_room_num };
            std::push_heap(room_heap.begin(), room_heap.end(), std::greater<room_t>());

            room_assigned = assigned_room_num;
        }
        assigned_rooms.at(order_in_input) = room_assigned;
    }

    std::cout << room_heap.size() << "\n";

    for (int assigned_room : assigned_rooms)
    {
        std::cout << assigned_room << " ";
    }
    std::cout << "\n";

    return 0;
}