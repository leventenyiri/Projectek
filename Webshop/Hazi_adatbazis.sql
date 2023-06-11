DROP DATABASE IF EXISTS WEBSHOP;

CREATE DATABASE WEBSHOP
	DEFAULT CHARACTER SET utf8mb4
    DEFAULT COLLATE utf8mb4_general_ci;
    
USE WEBSHOP;

CREATE TABLE Roles (
    Id INT PRIMARY KEY auto_increment,
    RoleName NVARCHAR(50) NOT NULL
);

CREATE TABLE Termek(

Id int PRIMARY KEY auto_increment,
Nev nvarchar(50) not null,
Ar int not null,
Db int not null,
Kategoria nvarchar(30)
);

CREATE TABLE Felhasznalo (

Id int PRIMARY KEY auto_increment,
Nev nvarchar(50) not null,
Jelszo nvarchar(255) not null,
Email nvarchar(50),
Cim nvarchar(50),
RoleId int,
CONSTRAINT FK_RoleId FOREIGN KEY (RoleId) REFERENCES Roles(Id)

);

CREATE TABLE Rendeles (

FelhasznaloId int,
TermekId int,
Datum datetime,
Darab int not null,

PRIMARY KEY(FelhasznaloId, TermekId, Datum),
CONSTRAINT FK_R_F FOREIGN KEY (FelhasznaloId) REFERENCES Felhasznalo(Id),
CONSTRAINT FK_R_T FOREIGN KEY (TermekId) REFERENCES Termek(Id)

);
INSERT INTO Roles (RoleName) VALUES ('Admin');
INSERT INTO Roles (RoleName) VALUES ('User');
INSERT INTO Roles (RoleName) VALUES ('OsAdmin');


INSERT INTO Termek (Nev, Ar, Db, Kategoria)
VALUES
    ('Csípős paprika', 500, 10, 'Paprika'),
    ('Fokhagymapor', 800, 5, 'Por'),
    ('Őrölt kömény', 350, 15, 'Magvak'),
    ('Cayenne bors', 450, 20, 'Bors'),
    ('Kurkuma', 600, 8, 'Fűszerek'),
    ('Cseresznyepaprika', 300, 12, 'Paprika'),
    ('Füstölt paprika', 700, 6, 'Paprika'),
    ('Szárított oregánó', 400, 18, 'Szárított Fűszerek'),
    ('Gyömbérpor', 550, 10, 'Por'),
    ('Szezámmag', 250, 25, 'Magvak');



INSERT INTO Felhasznalo (Nev, Jelszo, Email, Cim, RoleId)
VALUES
('Admin', '$2y$12$9xnPwQ2.DgVi9H1tLvguXucNnKn5jKf7SIwwg1JRnLrg5h1BSdtMC', 'admin@example.com', 'Budapest', 3),
('Péter Kovács', 'jelszo123', 'peter@example.com', 'Debrecen', 2),
('Katalin Nagy', 'kati456', 'katalin@example.com', 'Szeged', 2),
('Gábor Tóth', 'gabor789', 'gabor@example.com', 'Miskolc', 2),
('Anna Kovácsné', 'anna101', 'anna@example.com', 'Pécs', 2),
('Tamás Varga', 'tomi2022', 'tamas@example.com', 'Győr', 2),
('Mária Farkas', 'marika987', 'maria@example.com', 'Szombathely', 2),
('Zsolt Kiss', 'zsolt567', 'zsolt@example.com', 'Eger', 2),
('Erika Molnár', 'erika2023', 'erika@example.com', 'Nyíregyháza', 2),
('János Szabó', 'janos456', 'janos@example.com', 'Veszprém', 2);
  
INSERT INTO Rendeles (FelhasznaloId, TermekId, Datum, Darab) VALUES
  (1, 1, NOW(), 3),
  (2, 3, NOW(), 2),
  (3, 2, NOW(), 1),
  (4, 4, NOW(), 4),
  (5, 5, NOW(), 2),
  (1, 6, NOW(), 1),
  (2, 7, NOW(), 3),
  (3, 8, NOW(), 2),
  (4, 9, NOW(), 1),
  (5, 10, NOW(), 4);

select *from termek;

select *from felhasznalo;

select *from rendeles;

select *from roles;

