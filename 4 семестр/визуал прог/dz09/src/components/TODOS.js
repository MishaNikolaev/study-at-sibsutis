import DataApp from './DataApp';
import * as Yup from 'yup';

const TODOS = () => {
  const initialValues = {
    userId: '',
    title: '',
    completed: false
  };

  const validationSchema = Yup.object({
    userId: Yup.number().required('User ID is required'),
    title: Yup.string().required('Title is required'),
    completed: Yup.boolean()
  });

  const fields = [
    { name: 'userId', label: 'User ID', type: 'number' },
    { name: 'title', label: 'Title' },
    { name: 'completed', label: 'Completed', type: 'checkbox' }
  ];

  return (
    <DataApp
      endpoint="todos"
      initialValues={initialValues}
      validationSchema={validationSchema}
      fields={fields}
      checkboxStyle={{
        width: '20px',
        height: '20px',
        marginRight: '10px',
        verticalAlign: 'middle'
      }}
      checkboxLabelStyle={{
        display: 'flex',
        alignItems: 'center',
        fontSize: '16px',
        marginLeft: '-5px' 
      }}
    />
  );
};

export default TODOS;
