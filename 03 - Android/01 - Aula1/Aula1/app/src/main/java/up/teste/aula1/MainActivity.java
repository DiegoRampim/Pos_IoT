package up.teste.aula1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private EditText editText;
    private Button button;
    private ListView listView;
    private ArrayList<String> urlList;
    private AdapterListView adapterListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editText = (EditText)   findViewById(R.id.editTextUrl);
        button   = (Button)     findViewById(R.id.button);
        listView = (ListView)   findViewById(R.id.listView);

        editText.setText("http://");
        editText.setSelection(editText.getText().toString().length());

        urlList = new ArrayList<>();

        adapterListView = new AdapterListView(urlList);
        listView.setAdapter(adapterListView);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long l) {

                String url = urlList.get(position);
                //Toast.makeText(getApplicationContext(), url, Toast.LENGTH_SHORT).show();

                Intent intent = new Intent(MainActivity.this, WebViewActivity.class);
                intent.putExtra("url", url);
                startActivity(intent);


            }
        });

        button.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {

                String url = editText.getText().toString();

                if(!url.contains("http://") || !url.contains(".")){
                    editText.setError("URL inválida!");
                    return;
                }

                urlList.add(url);

                adapterListView.notifyDataSetChanged();

                editText.setText("http://");
                editText.setSelection(editText.getText().toString().length());

                Toast.makeText(getApplicationContext(), "Link salvo!", Toast.LENGTH_SHORT).show();

            }
        });

    }


}
