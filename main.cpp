#include <iostream>
#include <vector>
#include "subject.h"

int main() {
    std::vector<std::vector<Subject>> course;
    std::string name;
    int n_of_semesters, n_of_subjects;
    float grade;
    int ECTS, i, j;

    std::cout << "Enter the number of semesters: ";
    std::cin >> n_of_semesters;

    for (i = 0; i < n_of_semesters; ++i)
    {
        std::cout << "Enter the number of subjects in the " << i+1 << " semester: ";
        std::cin >> n_of_subjects;

        course.emplace_back();

        for (j = 0; j < n_of_subjects; ++j)
        {
            std::cout << "Subject: ";
            std::cin >> name;
            std::cout << "Grade: ";
            std::cin >> grade;
            std::cout << "ECTS: ";
            std::cin >> ECTS;

            course[i].emplace_back(name, grade, ECTS);
        }
    }

    std::cout << "\nYour report is ready!\n\n";
    float semester_grade, total_grade = 0;
    int semester_ECTS, total_ECTS = 0;

    for (i = 0; i < n_of_semesters; ++i)
    {
        semester_grade = 0.0f;
        semester_ECTS = 0;

        std::cout << "Semester " << i + 1 << ":\n";
        for (j = 0; j < course[i].size(); ++j)
        {
            Subject subject = course[i][j];
            grade = subject.getGrade();
            ECTS = subject.getECTS();
            std::cout << subject.getName() << " - "<< grade << std::endl;
            semester_grade += subject.getGrade() * float(ECTS);
            semester_ECTS += ECTS;
        }

        std::cout << "GPA: " << semester_grade / float(semester_ECTS) << ", Credits: " << semester_ECTS << " ECTS\n\n";
        total_grade += semester_grade;
        total_ECTS += semester_ECTS;

        if (n_of_semesters > 2 && (i+1) % 2 == 0)
        {
            std::cout << "Year " << i / 2 + 1 << ":\n" << "GPA: " << total_grade / float(total_ECTS) << ", Credits: " << total_ECTS << " ECTS\n\n";
        }
    }

    std::cout << "----------------------------------------------------------------\n\n";
    std::cout << "Total:\n" << "GPA: " << total_grade / float(total_ECTS) << ", Credits: " << total_ECTS << " ECTS\n";


    return 0;
}
