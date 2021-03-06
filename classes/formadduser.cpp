#include "formadduser.h"
#include "ui_formadduser.h"
#include <QMessageBox>
formAddUser::formAddUser(QWidget *parent = 0, usersmodelview *model = 0) : QDialog(parent),
                                                                           ui(new Ui::formAddUser), mod(model)
{
    ui->setupUi(this);
}

formAddUser::~formAddUser()
{
    delete ui;
}

void formAddUser::on_addUserCancel_clicked()
{
    this->close();
}

void formAddUser::on_addUser_clicked()
{

    if (ui->lineName->text().isEmpty() && ui->linePass->text().isEmpty() && ui->lineUN->text().isEmpty() && ui->lineSN->text().isEmpty())
    {
        QMessageBox e;
        e.warning(this, "Dati non validi", "Tutti i dati sono richiesti!");
        return;
    }
    else
    {

        for (int i = 0; i < mod->rowCount(QModelIndex()); i++)
        {
            if (ui->lineUN->text() == mod->data(mod->index(i, 0), Qt::DisplayRole).toString())
            {
                QMessageBox err3;
                err3.critical(this, "Conflitto", "Esiste gia un utente con quel username!");
                return;
            }
        }
        if (mod->addUser(ui->comboUType->currentText(), ui->lineName->text(), ui->lineSN->text(), ui->lineUN->text(), ui->linePass->text(), ui->dateofB->date()))
        {
            QMessageBox i;
            i.information(this, "Inserimento", "Utente inserito corretamente!");
        }
        else
        {
            QMessageBox er;
            er.critical(this, "Inserimento", "Errore durante inserimento! Impossibile inserire nuovo utente!");
        }
    }
    this->close();
}
