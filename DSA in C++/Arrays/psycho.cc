#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Struct to hold psychological metrics for a simulated character/NPC
struct PsychologicalProfile
{
    string name;
    int empathy;     // Scale 0-100
    int aggression;  // Scale 0-100
    int stressLevel; // Scale 0-100
    int rationality; // Scale 0-100

    // Method to classify behavior based on trait combinations
    string evaluateBehavior() const
    {
        if (aggression > 75 && empathy < 25)
        {
            return "Hostile / Unpredictable (High Risk)";
        }
        else if (stressLevel > 80 && rationality < 30)
        {
            return "Volatile / Erratic";
        }
        else if (empathy > 70 && rationality > 60)
        {
            return "Cooperative / Altruistic";
        }
        return "Stable / Neutral";
    }

    // Display profile details
    void printProfile() const
    {
        cout << "========================================\n";
        cout << "Subject Name: " << name << "\n";
        cout << "Empathy:      " << empathy << "/100\n";
        cout << "Aggression:   " << aggression << "/100\n";
        cout << "Stress Level: " << stressLevel << "/100\n";
        cout << "Rationality:  " << rationality << "/100\n";
        cout << "Behavior Classification: " << evaluateBehavior() << "\n";
        cout << "========================================\n\n";
    }
};

int main()
{
    // Vector storing multiple character profiles
    vector<PsychologicalProfile> subjects = {
        {"Subject A (Stable)", 80, 15, 20, 85},
        {"Subject B (Volatile)", 10, 90, 85, 20},
        {"Subject C (Neutral)", 50, 45, 50, 60}};

    // Iterate and evaluate each profile
    for (const auto &subject : subjects)
    {
        subject.printProfile();
    }

    return 0;
}