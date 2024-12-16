#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Function prototypes
void read_questions(const string& filename, vector<vector<string>>& questions);
void read_answers(const string& filename, vector<char>& answers);
void show_question(const vector<string>& question, char omit = ' ');
char player_try(const vector<string>& question, char omit = ' ');
void sort_score(vector<pair<string, int>>& scores, const string& player_name, int score);
int play_game(const string& player_name, const vector<vector<string>>& questions, const vector<char>& answers);
vector<pair<string, int>> read_scores();


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <questions_file> <answers_file> <seed>" << endl;
        return 1;
    }

    vector<vector<string>> questions;
    vector<char> answers;

    read_questions(argv[1], questions);
    read_answers(argv[2], answers);

    if (questions.size() != answers.size()) {
        cerr << "Error: Number of questions and answers do not match." << endl;
        return 1;
    }

    srand(stoi(argv[3]));

    vector<pair<string, int>> scores = read_scores();

    string player_name;
    cout << "Enter your name: ";
    getline(cin, player_name);

    int score = play_game(player_name, questions, answers);

    // Write score to summary.txt
    ofstream summary("summary.txt", ios::app);
    if (summary) {
        summary << player_name << " " << score << endl;
    } else {
        cerr << "Error: Unable to open summary.txt for writing." << endl;
    }
    summary.close();

    sort_score(scores, player_name, score);

    return 0;
}
// Implementing the functions

void read_questions(const string& filename, vector<vector<string>>& questions) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open questions file." << endl;
        exit(1);
    }

    string line;
    vector<string> question;
    while (getline(file, line)) {
        if (!line.empty()) {
            question.push_back(line);
            if (question.size() == 5) {
                questions.push_back(question);
                question.clear();
            }
        }
    }

    if (questions.empty()) {
        cerr << "Error: Question file is empty." << endl;
        exit(1);
    }

    file.close();
}

void read_answers(const string& filename, vector<char>& answers) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open answers file." << endl;
        exit(1);
    }

    char answer;
    while (file >> answer) {
        answer = toupper(answer);
        if (answer >= 'A' && answer <= 'D') {
            answers.push_back(answer);
        }
    }

    file.close();
}
void show_question(const string& player_name, int question_number, const vector<string>& question, char skipped_answer = ' ') {
    cout << player_name << " Here's Question Number " << question_number << endl;
    cout << question[0] << endl;
    for (size_t i = 1; i < question.size(); ++i) {
        char option = 'A' + static_cast<char>(i - 1);
        if (option != skipped_answer) {
            cout << option << ". " << question[i] << endl;
        }
    }
}
char player_try() {
    char choice;
    do {
        cout << "Your choice? > ";
        cin >> choice;
        choice = toupper(choice);
    } while (choice < 'A' || choice > 'D');
    return choice;
}


int play_game(const string& player_name, const vector<vector<string>>& questions, const vector<char>& answers) {
    int score = 0;
    int points = 10;
    vector<int> used_questions;

    for (size_t question_num = 1; question_num <= 6 && question_num <= questions.size(); ++question_num) {
        int index;
        do {
            index = rand() % questions.size();
        } while (find(used_questions.begin(), used_questions.end(), index) != used_questions.end());
        used_questions.push_back(index);

        show_question(player_name, question_num, questions[index]);

        char player_answer = player_try();
        if (player_answer == answers[index]) {
            cout << "You got that one right, for " << points << " points." << endl;
            score += points;
            points *= 10;
        } else {
            cout << "Incorrect. Would you like to try again? (Y/N) ";
            char retry;
            cin >> retry;
            if (toupper(retry) == 'Y') {
                show_question(player_name, question_num, questions[index], player_answer);
                player_answer = player_try();
                if (player_answer == answers[index]) {
                    int half_points = points / 2;
                    cout << "You got that one right, for " << half_points << " points." << endl;
                    score += half_points;
                    points = half_points * 10;
                } else {
                    cout << "Incorrect. Game over." << endl;
                    return 0;
                }
            } else {
                cout << "Skipping this question." << endl;
            }
        }
    }

    cout << "That's the end of the game, there are no more questions!" << endl;
    cout << player_name << ", your final score was: " << score << endl;
    cout << "This will be recorded to the game history file." << endl;

    return score;
}


void sort_score(vector<pair<string, int>>& scores, const string& player_name, int score) {
    scores.push_back({player_name, score});

    sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "The current record holder is " << scores[0].first << " with " << scores[0].second << " points." << endl;

    int rank = 1;
    for (const auto& s : scores) {
        if (s.first == player_name && s.second == score) {
            cout << "You have achieved rank " << rank << " with " << score << " points." << endl;
            break;
        }
        ++rank;
    }

    cout << "Thanks for playing, we hope you'll send all your friends to play." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ summary.txt ~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for (const auto& s : scores) {
        cout << s.first << " " << s.second << endl;
    }
}

vector<pair<string, int>> read_scores() {
    vector<pair<string, int>> scores;
    ifstream infile("summary.txt");
    string name;
    int score;
    while (infile >> name >> score) {
        scores.push_back({name, score});
    }
    infile.close();
    return scores;
}
