#pragma once

#include <string>
#include <QObject>
#include <QString>
#include <QDate>
#include <QDateTime>

class Patient
{
public:
    enum class Gender 
    {
        Unspecified = 0,
        Male,
        Female,
        Other
    };

    Q_GADGET
    Q_ENUM(Gender)

    Patient() = default;
    Patient(const QString& patient_id, const QString& first_name, 
            const QString& last_name, const QDate& date_of_birth,
            const Gender& gender);
    
    // Getters
    QString id() const;
    QString first_name() const;
    QString last_name() const;
    QDate date_of_birth() const;
    Gender gender() const;

    // Setters
    void id(const QString& id);
    void first_name(const QString& first_name);
    void last_name(const QString& last_name);
    void date_of_birth(const QDate& date_of_birth);
    void gender(const Gender& gender);

private:
    QString m_patient_id;
    QString m_first_name;
    QString m_last_name;
    QDate m_date_of_birth;
    Gender m_gender;
};



/*

// Patient.h
#pragma once

#include <QString>
#include <QDate>
#include <QMetaEnum>

namespace proto { class Patient; }

class Patient
{
public:
    enum class Gender {
        Unspecified = 0,
        Male,
        Female,
        Other
    };
    Q_GADGET
    Q_ENUM(Gender)

    int id;
    QString firstName;
    QString lastName;
    QDate dateOfBirth;
    Gender gender;

    // Conversion functions
    proto::Patient toProto() const;
    static Patient fromProto(const proto::Patient& proto);
};


*/


/*

// patient.proto
syntax = "proto3";

package proto;

import "google/protobuf/timestamp.proto";

enum Gender {
  GENDER_UNSPECIFIED = 0;
  MALE = 1;
  FEMALE = 2;
  OTHER = 3;
}

message Patient {
  int32 id = 1;
  string first_name = 2;
  string last_name = 3;
  google.protobuf.Timestamp date_of_birth = 4;
  Gender gender = 5;
}



*/