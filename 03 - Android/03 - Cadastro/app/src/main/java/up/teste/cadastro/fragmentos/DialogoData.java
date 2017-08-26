package up.teste.cadastro.fragmentos;


import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.Toast;

import up.teste.cadastro.R;
import up.teste.cadastro.interfaces.SelecaoDataListener;

public class DialogoData extends DialogFragment{

    private DatePicker datePicker;
    private Button button;
    private SelecaoDataListener selecaoDataListener;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.dialogo_data, container, false);

        datePicker = (DatePicker) view.findViewById(R.id.datePicker);
        button = (Button) view.findViewById(R.id.buttonSalvarData);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getDialog().dismiss();

                if(selecaoDataListener == null){
                    return;
                }

                int dia = datePicker.getDayOfMonth();
                int mes = datePicker.getMonth();
                int ano = datePicker.getYear();

                selecaoDataListener.dataSelecionada(dia, mes, ano);
            }
        });
        return view;
    }


    public SelecaoDataListener getSelecaoDataListener() {
        return selecaoDataListener;
    }

    public void setSelecaoDataListener(SelecaoDataListener selecaoDataListener) {
        this.selecaoDataListener = selecaoDataListener;
    }
}
