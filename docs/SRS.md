# Clinic Management System – Software Requirements Specification (SRS)

## 1. Introduction

### 1.1 Purpose
The Clinic Management System (CMS) is a desktop application for managing patient appointments, doctors, medical reports, and payments in a clinic. The system will allow clinic staff to efficiently schedule appointments, manage patient records, generate reports, and handle payments. The frontend will be a Qt6-based GUI client, and the backend will use gRPC + PostgreSQL for data management.

### 1.2 Scope
The system will support:
- Doctor, Patient, Appointment, and AppointmentReport management
- Payment handling with multiple currencies and methods
- Treatment tagging for medical reports
- CRUD operations for all entities
- Data consistency and basic validation rules

### 1.3 Definitions, Acronyms, and Abbreviations
- CMS: Clinic Management System
- GUI: Graphical User Interface
- CRUD: Create, Read, Update, Delete
- gRPC: Remote procedure call framework
- ERD: Entity-Relationship Diagram

<br>

## 2. Overall Description

### 2.1 Product Perspective
- The CMS will consist of two main modules:
- Frontend: Desktop Qt6 application that communicates with the backend via gRPC.
- Backend: gRPC server with PostgreSQL database.
The frontend and backend will be maintained in separate repositories, with the backend included as a submodule in the frontend repo for local development.

### 2.2 Product Functions
- The system supports the following main functions:
- Doctor Management: Add, view, update, delete, and list doctors
- Patient Management: Add, view, update, deactivate, and list patients
- Appointment Management: Schedule, reschedule, cancel, view appointments
- Appointment Reports: Create and view reports, assign treatment tags
- Treatment Tags: Create and manage tags for reports
- Payments: Record payments, split transactions, view patient payments
- Transactions: Track payment method, date, and amount for each transaction
- Payment Methods and Currencies: Manage available payment options and supported currencies

### 2.3 User Characteristics
- Receptionist: schedules appointments, records payments
- Doctor: views appointments, generates reports
- Admin: manages doctors, patients, and system configuration

### 2.4 Constraints
- Each appointment must have a doctor and a patient
- A report cannot exist without a completed appointment
- Payment total must equal the sum of its transactions
- Doctor cannot be deleted if they have future appointments

<br>

## 3. Functional Requirements

### 3.1 Doctor Management
- Add Doctor: Create a new doctor profile
- View Doctor: Display doctor details
- Update Doctor: Modify doctor profile
- Delete Doctor: Remove doctor if no future appointments exist
- List Doctors: Display all doctors

### 3.2 Patient Management
- Register Patient: Add new patient
- View Patient: Show patient profile and history
- Update Patient: Modify patient details
- Deactivate Patient: Remove access but archive history
- List Patients: Display all patients

### 3.3 Appointment Management
- Schedule Appointment: Assign doctor and patient
- Update Appointment: Reschedule or modify details
- Cancel Appointment: Remove an appointment
- List Appointments: Filter by doctor, patient, or date

### 3.4 Appointment Reports
- Create Report: Record appointment outcome
- Assign Treatment Tags: Attach relevant tags to reports
- Update Report: Edit report content
- View Reports: Retrieve by appointment or patient

### 3.5 Payment Management
- Record Payment: Add new payment
- Add Transactions: Multiple methods per payment
- View Payments: List payments per patient
- Verify Total: Ensure payment sum equals transaction sum

### 3.6 Payment Methods and Currencies
- Add Payment Method: Cash, Credit card, etc.
- Add Currency: Define new currency for payments
- List Methods/Currencies: Retrieve available options

<br>

## 4. Non-Functional Requirements
- Performance: Support up to 1000 patients and 50 doctors efficiently
- Usability: Intuitive GUI with Qt6 widgets
- Reliability: Backend must handle concurrent requests safely
- Maintainability: Clean separation of frontend and backend
- Portability: Desktop app for Windows and Linux

<br>

## 5. Entities (Nouns)
| Entity | Attributes | Relationships |
| --- | --- | --- |
| Doctor | id, first_name, last_name, dob, gender | has many Appointments |
| Patient | id, first_name, last_name, dob, gender | has many Appointments, has many Payments|
| Appointment | id, title, description, date, time | belongs to Doctor & Patient, may have one Report |
| AppointmentReport	| id, content, date, time | belongs to Appointment, has many TreatmentTags|
| TreatmentTag | id, name, description | belongs to many Reports |
| Payment | id, amount, currency_id | belongs to Patient, has many Transactions |
| PaymentTransaction | id, payment_id, amount, payment_method_id, date, time | belongs to Payment & PaymentMethod|
| PaymentMethod | id, name | used by many Transactions |
| Currency | id, name, code, symbol | used by many Payments |

<br>

## 6. Use Cases (Verbs)
- Doctor: Add, View, Update, Delete, List
- Patient: Register, View, Update, Deactivate, List
- Appointment: Schedule, Reschedule, Cancel, View
- Report: Create, Update, Assign Tags, View
- Treatment Tag: Create, List, Assign to Report
- Payment: Record, Add Transactions, View, Verify Total
- PaymentMethod/Currency: Add, List

<br>

## 7. Entity-Relationship Diagram (ERD)
<pre>
Doctor 1---* Appointment *---1 Patient
Appointment 1---0..1 AppointmentReport *---* TreatmentTag
Patient 1---* Payment 1---* PaymentTransaction *---1 PaymentMethod
Payment 1---1 Currency
</pre>

<br>

## 8. Constraints / Business Rules

1. Doctor cannot be deleted if future appointments exist
2. Appointment requires both doctor and patient
3. Report requires completed appointment
4. Payment total = sum of transactions
5. Transaction amounts must be ≥ 0
6. Supported currencies follow ISO 4217 standard

---

<br>

# CRUD Operations per Entity

## 1. Doctor
| Operation     | Description                               | gRPC Method Example      |
| ------------- | ----------------------------------------- | ------------------------ |
| Create Doctor | Add a new doctor profile                  | `CreateDoctor(Doctor)`   |
| Read Doctor   | Get doctor details by ID                  | `GetDoctor(DoctorId)`    |
| Update Doctor | Modify doctor info                        | `UpdateDoctor(Doctor)`   |
| Delete Doctor | Remove doctor (if no future appointments) | `DeleteDoctor(DoctorId)` |
| List Doctors  | Get all doctors                           | `ListDoctors(Empty)`     |

<br>

## 2. Patient
| Operation                 | Description               | gRPC Method Example            |
| ------------------------- | ------------------------- | ------------------------------ |
| Create Patient            | Register a new patient    | `CreatePatient(Patient)`       |
| Read Patient              | Get patient details by ID | `GetPatient(PatientId)`        |
| Update Patient            | Modify patient details    | `UpdatePatient(Patient)`       |
| Delete/Deactivate Patient | Archive patient profile   | `DeactivatePatient(PatientId)` |
| List Patients             | Retrieve all patients     | `ListPatients(Empty)`          |

<br>

## 3. Appointment
| Operation          | Description                                   | gRPC Method Example                |
| ------------------ | --------------------------------------------- | ---------------------------------- |
| Create Appointment | Schedule new appointment                      | `CreateAppointment(Appointment)`   |
| Read Appointment   | Get appointment by ID                         | `GetAppointment(AppointmentId)`    |
| Update Appointment | Modify appointment details (reschedule, edit) | `UpdateAppointment(Appointment)`   |
| Delete Appointment | Cancel appointment                            | `DeleteAppointment(AppointmentId)` |
| List Appointments  | View appointments by doctor, patient, or date | `ListAppointments(Filter)`         |

<br>

## 4. Appointment Report
| Operation     | Description                         | gRPC Method Example      |
| ------------- | ----------------------------------- | ------------------------ |
| Create Report | Add report to appointment           | `CreateReport(Report)`   |
| Read Report   | View report details                 | `GetReport(ReportId)`    |
| Update Report | Edit report content                 | `UpdateReport(Report)`   |
| Delete Report | Remove report                       | `DeleteReport(ReportId)` |
| List Reports  | View reports by appointment/patient | `ListReports(Filter)`    |

<br>

## 5. Treatment Tag
| Operation              | Description               | gRPC Method Example                  |
| ---------------------- | ------------------------- | ------------------------------------ |
| Create Tag             | Define new treatment type | `CreateTag(Tag)`                     |
| Read Tag               | Get tag details           | `GetTag(TagId)`                      |
| Update Tag             | Edit tag info             | `UpdateTag(Tag)`                     |
| Delete Tag             | Remove tag                | `DeleteTag(TagId)`                   |
| List Tags              | Show all tags             | `ListTags(Empty)`                    |
| Assign Tag to Report   | Link tag with report      | `AssignTagToReport(TagReportLink)`   |
| Remove Tag from Report | Unlink tag                | `RemoveTagFromReport(TagReportLink)` |

<br>

## 6. Payment
| Operation      | Description                    | gRPC Method Example        |
| -------------- | ------------------------------ | -------------------------- |
| Create Payment | Add new payment record         | `CreatePayment(Payment)`   |
| Read Payment   | Get payment details            | `GetPayment(PaymentId)`    |
| Update Payment | Edit payment info              | `UpdatePayment(Payment)`   |
| Delete Payment | Cancel/remove payment          | `DeletePayment(PaymentId)` |
| List Payments  | View all payments (by patient) | `ListPayments(PatientId)`  |
| Verify Payment | Validate sum of transactions   | `VerifyPayment(PaymentId)` |

<br>

## 7. Payment Transaction
| Operation          | Description                     | gRPC Method Example                |
| ------------------ | ------------------------------- | ---------------------------------- |
| Create Transaction | Record payment transaction      | `CreateTransaction(Transaction)`   |
| Read Transaction   | Get transaction by ID           | `GetTransaction(TransactionId)`    |
| Update Transaction | Edit transaction                | `UpdateTransaction(Transaction)`   |
| Delete Transaction | Remove transaction              | `DeleteTransaction(TransactionId)` |
| List Transactions  | Show transactions for a payment | `ListTransactions(PaymentId)`      |

<br>

## 8. Payment Method
| Operation     | Description               | gRPC Method Example           |
| ------------- | ------------------------- | ----------------------------- |
| Create Method | Define new payment method | `CreateMethod(PaymentMethod)` |
| Read Method   | Get method details        | `GetMethod(MethodId)`         |
| Update Method | Edit method info          | `UpdateMethod(PaymentMethod)` |
| Delete Method | Remove method             | `DeleteMethod(MethodId)`      |
| List Methods  | Show all payment methods  | `ListMethods(Empty)`          |

<br>

## 9. Currency
| Operation       | Description                   | gRPC Method Example          |
| --------------- | ----------------------------- | ---------------------------- |
| Create Currency | Define new currency           | `CreateCurrency(Currency)`   |
| Read Currency   | Get currency details          | `GetCurrency(CurrencyId)`    |
| Update Currency | Edit currency info            | `UpdateCurrency(Currency)`   |
| Delete Currency | Remove currency               | `DeleteCurrency(CurrencyId)` |
| List Currencies | Show all supported currencies | `ListCurrencies(Empty)`      |
