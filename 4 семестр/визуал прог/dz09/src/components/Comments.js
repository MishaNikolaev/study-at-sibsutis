import DataApp from './DataApp';
import * as Yup from 'yup';

const Comments = () => {
  const initialValues = {
    postId: '',
    name: '',
    email: '',
    body: ''
  };

  const validationSchema = Yup.object({
    postId: Yup.number().required('Post ID is required'),
    name: Yup.string().required('Name is required'),
    email: Yup.string().email('Invalid email'),
    body: Yup.string().required('Body is required')
  });

  const fields = [
    { name: 'postId', label: 'Post ID', type: 'number' },
    { name: 'name', label: 'Name' },
    { name: 'email', label: 'Email', type: 'email' },
    { name: 'body', label: 'Body', as: 'textarea' }
  ];

  return (
    <DataApp
      endpoint="comments"
      initialValues={initialValues}
      validationSchema={validationSchema}
      fields={fields}
      formStyle={{
        display: 'grid',
        gridTemplateColumns: '1fr 1fr',
        gap: '20px',
        maxWidth: '800px',
        margin: '0 auto'
      }}
      fieldStyle={{
        marginBottom: '15px'
      }}
      inputStyle={{
        width: '100%',
        padding: '10px',
        border: '1px solid #ddd',
        borderRadius: '4px',
        fontSize: '16px',
        boxSizing: 'border-box'
      }}
      textareaStyle={{
        width: '100%',
        padding: '10px',
        border: '1px solid #ddd',
        borderRadius: '4px',
        fontSize: '16px',
        minHeight: '100px',
        resize: 'vertical',
        boxSizing: 'border-box'
      }}
      labelStyle={{
        display: 'block',
        marginBottom: '5px',
        fontWeight: '500',
        color: '#333'
      }}
      errorStyle={{
        color: '#d32f2f',
        fontSize: '14px',
        marginTop: '5px'
      }}
    />
  );
};

export default Comments;
