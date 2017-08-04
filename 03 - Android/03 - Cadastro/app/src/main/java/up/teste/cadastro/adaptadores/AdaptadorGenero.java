package up.teste.cadastro.adaptadores;

import android.database.DataSetObserver;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.SpinnerAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class AdaptadorGenero extends BaseAdapter implements SpinnerAdapter {

    private ArrayList<String> generos;

    public AdaptadorGenero(ArrayList<String> generos) {
        this.generos = generos;
    }


    @Override
    public int getCount() {
        return generos.size();
    }

    @Override
    public Object getItem(int i) {
        return generos.get(i);
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    @Override
    public boolean hasStableIds() {
        return false;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {

        TextView textView = null;

        if(view == null){
            textView = new TextView(viewGroup.getContext());
        }else{
            textView = (TextView) view;
        }

        String genero = generos.get(i);

        textView.setText(genero);

        textView.setPadding(0,10,10,10);

        return textView;
    }
}
