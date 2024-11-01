#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

class HoneyToken {
   private:
       string tokenID;
       string fakeUsername;
       string fakePassword;
       bool wasAccessed;
       time_t timeCreated;
       vector<string> accessAttempts;

   public:
       HoneyToken(string id, string username, string password) {
           tokenID = id;
           fakeUsername = username;
           fakePassword = password;
           wasAccessed = false;
           timeCreated = time(0);
       }

       string getID() { return tokenID; }
       string getUsername() { return fakeUsername; }
       string getPassword() { return fakePassword; }
       bool getWasAccessed() { return wasAccessed; }

       void logAccess(string ipAddress) {
           wasAccessed = true;
           accessAttempts.push_back(ipAddress);
           cout << "ALERT: HoneyToken " << tokenID << " was accessed by " << ipAddress << "!" << endl;
       }

       void printInfo() {
           cout << "Token ID: " << tokenID << endl;
           cout << "Username: " << fakeUsername << endl;
           cout << "Password: " << fakePassword << endl;
           cout << "Was Accessed: " << (wasAccessed ? "Yes" : "No") << endl;
           cout << "Access Attempts: " << accessAttempts.size() << endl;
       }
};

class PhishingDetector {
   private:
       vector<HoneyToken> honeyTokens;
       map<string, int> suspiciousIPs;

   public:
       void createToken(string id, string username, string password) {
           HoneyToken newToken(id, username, password);
           honeyTokens.push_back(newToken);
           cout << "Created new honey token with ID: " << id << endl;
       }

       void simulateAccess(string tokenID, string ipAddress) {
           bool tokenFound = false;

           for (int i = 0; i < honeyTokens.size(); i++) {
               if (honeyTokens[i].getID() == tokenID) {
                   tokenFound = true;
                   honeyTokens[i].logAccess(ipAddress);

                   if (suspiciousIPs.find(ipAddress) != suspiciousIPs.end()) {
                       suspiciousIPs[ipAddress]++;
                   } else {
                       suspiciousIPs[ipAddress] = 1;
                   }

                   if (suspiciousIPs[ipAddress] > 2) {
                       cout << "WARNING: IP " << ipAddress << " has made multiple access attempts!" << endl;
                   }
               }
           }

           if (!tokenFound) {
               cout << "Error: HoneyToken with ID " << tokenID << " not found." << endl;
           }
       }

       void printAllTokens() {
           cout << "\nAll Honey Tokens:" << endl;
           cout << "----------------" << endl;
           for (int i = 0; i < honeyTokens.size(); i++) {
               honeyTokens[i].printInfo();
               cout << "----------------" << endl;
           }
       }
};

int main() {
   PhishingDetector detector;

   detector.createToken("HT001", "fake_user1", "password123!");
   detector.createToken("HT002", "admin_test", "admin123!");

   detector.simulateAccess("HT001", "192.168.1.100");
   detector.simulateAccess("HT001", "192.168.1.100");
   detector.simulateAccess("HT002", "192.168.1.100");
   detector.simulateAccess("HT001", "192.168.1.101");

   detector.printAllTokens();

   return 0;
}
