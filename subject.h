//
// Created by Siarhei on 5/23/2023.
//

#ifndef CGPA_CALCULATOR_SUBJECT_H
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Subject
{
private:
    std::string name;
    float grade;
    int ECTS;
    std::vector<float> valid_grades = {2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f};

public:
    Subject(std::string _name, float _grade, int _ECTS):
            name(std::move(_name)),
            grade(_grade),
            ECTS(_ECTS)
    {
        if (std::find(valid_grades.begin(), valid_grades.end(), grade) == valid_grades.end())
        {
            throw std::runtime_error("Not a valid grade");
        }

        if (ECTS <= 0)
        {
            throw std::runtime_error("Credit must be represented by a positive integer");
        }
    }

    std::string getName() const { return name; }

    float getGrade() const { return grade; }

    int getECTS() const { return ECTS; }
};

#define CGPA_CALCULATOR_SUBJECT_H

#endif //CGPA_CALCULATOR_SUBJECT_H
