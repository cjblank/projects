#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

atomic<int> o_counter; // oxygen counter
atomic<int> h_counter; // hydrogen counter
atomic<int> c_counter; // carbon counter
atomic<int> water_counter;
atomic<int> ozone_counter;
atomic<int> ethanol_counter;
atomic<int> molecule_counter; // counts total number of molecules made
atomic<bool> in_molecule;

mutex m; // lock used for functionality of program
condition_variable cv;
mutex m2; // lock used for output
condition_variable cv2;

void OArrives() {
	while (molecule_counter < 300) {
		o_counter += 2;
		m2.lock(); // lock created for output to work correctly
		cout << "Oxygen producer runs - Produces 2 (O=" << o_counter << ")" << endl;
		m2.unlock();
		this_thread::sleep_for(chrono::milliseconds(10)); // make the thread wait for 10 milliseconds while other threads run
		cv.notify_one(); // sends notification to condition variables so that they can check to see if there is a sufficient number of atoms to make a molecule
	}
}

void HArrives() {
	while (molecule_counter < 300) {
		h_counter += 4;
		m2.lock(); // lock created for output to work correctly
		cout << "Hydrogen producer runs - Produces 4 (H=" << h_counter << ")" << endl;
		m2.unlock();
		this_thread::sleep_for(chrono::milliseconds(25)); // make the thread wait for 25 milliseconds while other threads run
		cv.notify_one(); // sends notification to condition variables so that they can check to see if there is a sufficient number of atoms to make a molecule
	}
}

void CArrives() {
	while (molecule_counter < 300) {
		c_counter += 2;
		m2.lock(); // lock created for output to work correctly
		cout << "Carbon producer runs - Produces 2 (C=" << c_counter << ")" << endl;
		m2.unlock();
		this_thread::sleep_for(chrono::milliseconds(50)); // make the thread wait for 50 milliseconds while other threads run
		cv.notify_one(); // sends notification to condition variables so that they can check to see if there is a sufficient number of atoms to make a molecule
	}
}

void MakeWater() {
	unique_lock<mutex> lk(m);
	while (water_counter < 100) {
        // condition variable used to check if enough atoms are present in order to make molecule
		cv.wait(lk, [] {return (h_counter >= 2) && (o_counter >= 1); });

        // produces water molecule
		o_counter--;
		h_counter -= 2;
		water_counter++;
		molecule_counter++;

		m2.lock(); // lock created for output to work correctly
		cout << "Water consumer runs, consume H20;  H= " << h_counter << ", O= " << o_counter << endl;
		m2.unlock();

		this_thread::sleep_for(chrono::milliseconds(20)); // make the thread wait for 20 milliseconds while other threads run
	}
}

void MakeOzone() {
	unique_lock<mutex> lk(m);
	while (ozone_counter < 100) {
        // condition variable used to check if enough atoms are present in order to make molecule
		cv.wait(lk, [] {return o_counter >= 3; });

        // produces ozone molecule
		o_counter -= 3;
		ozone_counter++;
		molecule_counter++;

		m2.lock(); // lock created for output to work correctly
		cout << "Ozone consumer runs - consumes O3; O= " << o_counter << endl;
		m2.unlock();

		this_thread::sleep_for(chrono::milliseconds(20)); // make the thread wait for 20 milliseconds while other threads run
	}
}

void MakeEthanol() {
	unique_lock<mutex> lk(m);
	while (ethanol_counter < 100) {
        // condition variable used to check if enough atoms are present in order to make molecule
		cv.wait(lk, [] {return (c_counter >= 2) && (h_counter >= 6) && (o_counter >= 1); });

        // produces ethanol molecule
		o_counter--;
		h_counter -= 6;
		c_counter -= 2;
		ethanol_counter++;
		molecule_counter++;

		m2.lock(); // lock created for output to work correctly
		cout << "Ethanol consumer runs - consumes C2H6O; C= " << c_counter << ", H= " << h_counter << ", O= " << o_counter << endl;
		m2.unlock();

		this_thread::sleep_for(chrono::milliseconds(20)); // make the thread wait for 20 milliseconds while other threads run
	}
}

int main() {
        o_counter = 0;
        h_counter = 0;
        c_counter = 0;
        molecule_counter = 0;
        ethanol_counter = 0;
        ozone_counter = 0;
        water_counter = 0;
        in_molecule = false;

	auto start = chrono::high_resolution_clock::now(); // starts execution clock

    // creates a thread for each resource
	thread oxygen(OArrives);
	thread hydrogen(HArrives);
	thread carbon(CArrives);
	thread water(MakeWater);
	thread ozone(MakeOzone);
	thread alcohol(MakeEthanol);

    // returns each thread after they're doen running
    oxygen.join();
	hydrogen.join();
	carbon.join();
	water.join();
	ozone.join();
	alcohol.join();

	auto done = chrono::high_resolution_clock::now(); // ends execution clock

	cout << "\n\n\n\nCarbon Atoms produced: " << c_counter << endl;
	cout << "Hydrogen Atoms produced: " << h_counter << endl;
	cout << "Oygen Atoms produced: " << o_counter << endl;
	cout << ethanol_counter << " Ethanol molecules produced\n";
	cout << water_counter << " Water molecules produced\n";
	cout << ozone_counter << " Ozone molecules produced\n";
	cout << "Time to finish execution: " << chrono::duration_cast<chrono::milliseconds>(done - start).count() << "ms" << endl;

	return 0;
}
