#include "Patient.h"


Patient::Patient(const QString& patient_id, const QString& first_name, 
        const QString& last_name, const QDate& date_of_birth,
        const Gender& gender)
    : m_patient_id {patient_id}, m_first_name {first_name}
    , m_last_name {last_name}, m_date_of_birth {date_of_birth}
    , m_gender {gender}
{}

// Getters
QString Patient::id() const {
    return m_patient_id;
}


QString Patient::first_name() const {
    return m_first_name;
}


QString Patient::last_name() const {
    return m_last_name;
}


QDate Patient::date_of_birth() const {
    return m_date_of_birth;
}


Patient::Gender Patient::gender() const {
    return m_gender;
}


// Setters
void Patient::id(const QString& id) {
    m_patient_id = id;
}


void Patient::first_name(const QString& first_name) {
    m_first_name = first_name;
}


void Patient::last_name(const QString& last_name) {
    m_last_name = last_name;
}


void Patient::date_of_birth(const QDate& date_of_birth) {
    m_date_of_birth = date_of_birth;
}


void Patient::gender(const Gender& gender) {
    m_gender = gender;
}



/*

// Patient.cpp
#include "Patient.h"
#include "patient.pb.h"
#include <google/protobuf/timestamp.pb.h>

proto::Patient Patient::toProto() const
{
    proto::Patient proto;
    proto.set_id(id);
    proto.set_first_name(firstName.toStdString());
    proto.set_last_name(lastName.toStdString());

    // Convert QDate -> Timestamp
    QDateTime dt(dateOfBirth, QTime(0, 0)); // midnight
    qint64 epochSecs = dt.toSecsSinceEpoch();

    google::protobuf::Timestamp* timestamp = new google::protobuf::Timestamp();
    timestamp->set_seconds(epochSecs);
    proto.set_allocated_date_of_birth(timestamp);

    // Convert gender
    proto::Gender g;
    switch (gender) {
        case Gender::Male: g = proto::MALE; break;
        case Gender::Female: g = proto::FEMALE; break;
        case Gender::Other: g = proto::OTHER; break;
        default: g = proto::GENDER_UNSPECIFIED;
    }
    proto.set_gender(g);

    return proto;
}

Patient Patient::fromProto(const proto::Patient& proto)
{
    Patient p;
    p.id = proto.id();
    p.firstName = QString::fromStdString(proto.first_name());
    p.lastName = QString::fromStdString(proto.last_name());

    // Convert Timestamp -> QDate
    if (proto.has_date_of_birth()) {
        qint64 seconds = proto.date_of_birth().seconds();
        QDateTime dt = QDateTime::fromSecsSinceEpoch(seconds);
        p.dateOfBirth = dt.date();
    } else {
        p.dateOfBirth = QDate(); // null date
    }

    // Convert gender
    switch (proto.gender()) {
        case proto::MALE: p.gender = Gender::Male; break;
        case proto::FEMALE: p.gender = Gender::Female; break;
        case proto::OTHER: p.gender = Gender::Other; break;
        default: p.gender = Gender::Unspecified;
    }

    return p;
}


*/