package up.teste.aula1;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class AdapterListView extends BaseAdapter {

    private ArrayList<String> strings;

    public AdapterListView(ArrayList<String> strings) {
        this.strings = strings;
    }

    @Override
    public int getCount() {
        return strings.size();
    }

    @Override
    public Object getItem(int i) {
        return strings.get(i);
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    @Override
    public View getView(int position, View view, ViewGroup viewGroup) {

        Context context = viewGroup.getContext();

        TextView textView = new TextView(context);

        textView.setPadding(10, 30, 10, 30);
        textView.setTextSize(16);

        String url = strings.get(position);

        textView.setText(url);

        return textView;
    }
}
