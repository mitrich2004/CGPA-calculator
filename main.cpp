#include <iostream>
#include <vector>
#include "subject.h"
#include <fstream>
#include <sstream>

std::vector<std::vector<Subject>> read_file(const std::string &filename)
{
    std::vector<std::vector<Subject>> course;
    int n_of_semesters = 0;
    std::ifstream file_in;
    file_in.open(filename);

    std::string line;
    std::string item;

    while (std::getline(file_in, line))
    {
        std::stringstream line_stream(line);
        std::vector<std::string> data;

        while (std::getline(line_stream, item, ','))
        {
            data.push_back(item);
        }

        if (data.size() == 1)
        {
            course.emplace_back();
            ++n_of_semesters;
        }
        else if (data.size() == 3)
        {
            course[n_of_semesters-1].emplace_back(data[0], std::stof(data[1]), std::stoi(data[2]));
        }
    }

    file_in.close();

    return course;
}

void write_file(std::vector<std::vector<Subject>> &course, const std::string &filename)
{
    float grade;
    int ECTS, i, j;

    std::ofstream file_out;
    file_out.open(filename);

    size_t n_of_semesters = course.size();
    float semester_grade, total_grade = 0.0f;
    int semester_ECTS, total_ECTS = 0;

    for (i = 0; i < n_of_semesters; ++i)
    {
        semester_grade = 0.0f;
        semester_ECTS = 0;

        file_out << "Semester " << i + 1 << ":\n";
        for (j = 0; j < course[i].size(); ++j)
        {
            Subject subject = course[i][j];
            grade = subject.getGrade();
            ECTS = subject.getECTS();
            file_out << subject.getName() << " - "<< grade << std::endl;
            semester_grade += subject.getGrade() * float(ECTS);
            semester_ECTS += ECTS;
        }

        file_out << "GPA: " << semester_grade / float(semester_ECTS) << ", Credits: " << semester_ECTS << " ECTS\n\n";
        total_grade += semester_grade;
        total_ECTS += semester_ECTS;

        if (n_of_semesters > 2 && (i+1) % 2 == 0)
        {
            file_out << "Year " << i / 2 + 1 << ":\n" << "GPA: " << total_grade / float(total_ECTS) << ", Credits: " << total_ECTS << " ECTS\n\n";
            file_out << "----------------------------------------------------------------\n\n";
        }
    }

    file_out << "----------------------------------------------------------------\n\n";
    file_out << "Total:\n" << "GPA: " << total_grade / float(total_ECTS) << ", Credits: " << total_ECTS << " ECTS\n";

    file_out.close();
}

int main()
{
    std::vector<std::vector<Subject>> course;
    std::string file_in, file_out;

    std::cout << "Greetings! Let us calculate your GPA!\n";

    std::cout << "Please let me know the name of the file with your grades: ";
    std::cin >> file_in;

    std::cout << "Please let me know to which file should I save your report: ";
    std::cin >> file_out;

    course = read_file(file_in);
    write_file(course, file_out);

    std::cout << "\nYour report is ready!\n";

    /*std::cout << "Enter the number of semesters: ";
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

        file_out << "Semester " << i + 1 << ":\n";
        for (j = 0; j < course[i].size(); ++j)
        {
            Subject subject = course[i][j];
            grade = subject.getGrade();
            ECTS = subject.getECTS();
            file_out << subject.getName() << " - "<< grade << std::endl;
            semester_grade += subject.getGrade() * float(ECTS);
            semester_ECTS += ECTS;
        }

        file_out << "GPA: " << semester_grade / float(semester_ECTS) << ", Credits: " << semester_ECTS << " ECTS\n\n";
        total_grade += semester_grade;
        total_ECTS += semester_ECTS;

        if (n_of_semesters > 2 && (i+1) % 2 == 0)
        {
            file_out << "Year " << i / 2 + 1 << ":\n" << "GPA: " << total_grade / float(total_ECTS) << ", Credits: " << total_ECTS << " ECTS\n\n";
        }
    }

    file_out << "----------------------------------------------------------------\n\n";
    file_out << "Total:\n" << "GPA: " << total_grade / float(total_ECTS) << ", Credits: " << total_ECTS << " ECTS\n";*/

    return 0;
}
